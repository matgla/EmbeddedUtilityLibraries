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

constexpr static uint8_t reverse_lookup[16] = {
    0b0000, 0b1000, 0b0100, 0b1100,
    0b0010, 0b1010, 0b0110, 0b1110,
    0b0001, 0b1001, 0b0101, 0b1101,
    0b0011, 0b1011, 0b0111, 0b1111
};

constexpr uint8_t reverse(const uint8_t byte)
{
    return reverse_lookup[(byte >> 4) & 0xf] 
        | (reverse_lookup[byte & 0xf] << 4);
}

template <uint32_t polynomial, uint32_t crc_size>
constexpr std::array<uint32_t, 256> generate_table()
{
    std::array<uint32_t, 256> table;
    for (uint32_t i = 0; i < 256; ++i)
    {
        uint32_t remainder = i;
        for (uint32_t bit = 0; bit < 8; ++bit)
        {
            remainder = (remainder & 1) == 1  
                ? (remainder >> 1) ^ polynomial
                : remainder >> 1;
        }
        table[i] = remainder;
    }
    return table;
}

constexpr uint32_t reverse(uint32_t data)
{
    return reverse(static_cast<uint8_t>(data)) << 24
            | reverse(static_cast<uint8_t>(data >> 8)) << 16
            | reverse(static_cast<uint8_t>(data >> 16)) << 8
            | reverse(static_cast<uint8_t>(data >> 24)) << 0;
}

template <uint32_t crc_size, uint32_t polynomial>
uint32_t calculate_crc(const std::span<uint8_t>& data)
{
    constexpr static auto table = generate_table<reverse(0x04C11DB7u), 32>();
    uint32_t crc = 0xffffffffu;
    for (const auto byte : data)
    {
        crc = table[(crc ^ byte) & 0xff] ^ (crc >> 8);
    }
    return ~crc;
}

template <uint32_t polynomial = 0x04c11db7>
uint32_t calculate_crc32(const std::span<uint8_t>& data)
{
    return calculate_crc<32, polynomial>(data);
}
