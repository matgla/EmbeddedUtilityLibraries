// This file is part of EmbeddedUtilityLibraries project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once 

#include <array>
#include <cstdint>
#include <cstdio>

#include <span>

constexpr static std::array<uint8_t, 16> reverse_lookup = {
    0b0000, 0b1000, 0b0100, 0b1100,
    0b0010, 0b1010, 0b0110, 0b1110,
    0b0001, 0b1001, 0b0101, 0b1101,
    0b0011, 0b1011, 0b0111, 0b1111
};

constexpr uint8_t reverse(const uint8_t byte)
{
    return static_cast<uint8_t>(reverse_lookup[(byte >> 4u) & 0xfu] // NOLINT (cppcoreguidelines-pro-bounds-constant-array-index)
        | (reverse_lookup[byte & 0xfu] << 4u)); // NOLINT (cppcoreguidelines-pro-bounds-constant-array-index)
}

template <typename T>
constexpr T get_mask()
{
    if constexpr (sizeof(T) == 1)
    {
        return 0x80;
    }
    if constexpr (sizeof(T) == 2)
    {
        return 0x8000;
    }
    if constexpr (sizeof(T) == 4)
    {
        return 0x80000000;
    }
}

template <typename T>
constexpr T get_bits()
{
    return sizeof(T) * 8;
}

constexpr uint32_t table_size = 256;

constexpr std::array<uint32_t, table_size> generate_table(uint32_t polynomial)
{
    std::array<uint32_t, table_size> table{};
    for (uint32_t i = 0; i < table_size; ++i)
    {
        uint32_t crc = i;
        for (uint32_t bit = 0; bit < 8; ++bit)
        {
            crc = (crc >> 1) ^ ((crc & 0x1u) != 0u ? polynomial : 0);
        }
        table.at(i) = crc;
    }
    return table;
}

constexpr std::array<uint8_t, table_size> generate_table(uint8_t polynomial)
{
    std::array<uint8_t, table_size> table{};
    for (uint32_t i = 0; i < table_size; ++i)
    {
        auto crc = static_cast<uint8_t>(i);
        for (uint32_t bit = 0; bit < 8; ++bit)
        {
            crc = static_cast<uint8_t>(((crc & 0x80) != 0 ? (crc << 1) ^ polynomial : crc << 1));
        }
        table.at(i) = crc;
    }
    return table;
}


constexpr std::array<uint16_t, table_size> generate_table(uint16_t polynomial)
{
    std::array<uint16_t, table_size> table{};
    for (uint32_t i = 0; i < table_size; ++i)
    {
        uint16_t crc = static_cast<uint16_t>(i);
        for (uint32_t bit = 0; bit < 16; ++bit)
        {
            crc = static_cast<uint16_t>(((crc & 0x8000) != 0 ? (crc << 1) ^ polynomial : crc << 1));
        }
        table.at(i) = crc;
    }
    return table;
}

constexpr uint32_t reverse(const uint32_t data)
{
    return static_cast<uint32_t>(reverse(static_cast<uint8_t>(data)) << 24
            | reverse(static_cast<uint8_t>(data >> 8)) << 16
            | reverse(static_cast<uint8_t>(data >> 16)) << 8
            | reverse(static_cast<uint8_t>(data >> 24)) << 0);
}

constexpr uint16_t reverse(const uint16_t data) 
{
    return static_cast<uint16_t>(
        reverse(static_cast<uint8_t>(data)) << 8
        | reverse(static_cast<uint8_t>(data >> 8)) << 0
    );
}

inline uint8_t calculate_part(uint8_t crc, uint8_t val)
{
    static_cast<void>(crc);
    return val;
}

inline uint16_t calculate_part(uint16_t crc, uint16_t val) 
{
    static_cast<void>(crc);
    return static_cast<uint16_t>(crc << 8) ^ val;
}

inline uint32_t calculate_part(uint32_t crc, uint32_t val)
{
    return val ^ (crc >> 8);
}

inline uint32_t get_index_for_table(uint32_t crc, uint8_t byte)
{
    return (crc ^ byte) & 0xff; 
}

inline uint8_t get_index_for_table(uint8_t crc, uint8_t byte)
{
    return (crc ^ byte) & 0xff; 
}

inline uint16_t get_index_for_table(uint16_t crc, uint8_t byte)
{
    return ((crc >> 8) ^ byte) & 0xff; 
}

template <typename T, T polynomial, T xor_out, bool reflected>
T calculate_crc(const std::span<const uint8_t>& data, T init)
{
    constexpr static T target_polynomial = reflected ? reverse(polynomial) : polynomial;
    constexpr static std::array<T, 256> table = generate_table(target_polynomial);
    T crc                       = init;
    for (const auto byte : data)
    {
        crc = calculate_part(crc, table.at(get_index_for_table(crc, byte)));
    }
    return crc ^ xor_out;
}

template <uint32_t polynomial = 0x04c11db7>
uint32_t calculate_crc32(const std::span<const uint8_t> data)
{
    return calculate_crc<uint32_t, polynomial, std::numeric_limits<uint32_t>::max(), true>(data, std::numeric_limits<uint32_t>::max());
}

template <uint8_t polynomial = 0x07>
uint8_t calculate_crc8(const std::span<const uint8_t> data)
{
    return calculate_crc<uint8_t, polynomial, 0, false>(data, 0);
}

constexpr uint16_t ccit_polynomial = 0x1021;

template <uint16_t polynomial = 0x1021>
uint16_t calculate_crc16(const std::span<const uint8_t> data)
{
    if constexpr (ccit_polynomial == polynomial)
    {
        return calculate_crc<uint16_t, polynomial, 0, false>(data, 0);
    }
    else
    {
        return 0;
    }
}

