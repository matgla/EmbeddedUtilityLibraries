// This file is part of EmbeddedUtilityLibraries project.
// Copyright (C) 2022 Mateusz Stadnik
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
#include <span>
#include <string_view>

#include "detail/crc_utils.hpp"

#include "eul/utils/unused.hpp"

namespace eul::crc
{

/**
 * @ingroup crc
 * @brief Computes the CRC value for any configuration
 * 
 * This class uses compile-time generation of the lookup table. 
 * Each lookup table costs 256 bytes of memory.
 * 
 * @tparam T underlaying type for calculations and return value
 * @tparam polynomial polynomial for CRC algorithm, must fit in sizeof(T)
 * @tparam xor_out value for xor operation for final value 
 * @tparam init value to initialize CRC register
 * @tparam refin reflect input data
 * @tparam refout reflect final value
 * @tparam bits size of CRC register in bits
 * 
 */

template <typename T, T polynomial, T xor_out, T init, bool refin, bool refout, uint8_t bits>
class Crc
{
public: 
    /**
     * @brief Alias for data view to pass input data
     * 
     */
    using DataType = std::span<const uint8_t>;

    /**
     * @brief Computes CRC value for input data
     * 
     * @param data input bytes for CRC calculation
     * @return CRC calculated for input data
     */
    static constexpr T calculate(DataType data)
    {

        auto crc = static_cast<T>(init << crc_offset);

        constexpr uint64_t bits_offset = sizeof(T) * 8 - bits;
        constexpr T mask = T(~T(0)) >> bits_offset;
        constexpr T offset = (sizeof(T) - 1) * 8;
        for (const auto byte : data)
        {
            if constexpr (!refin)
            {
                const auto position = static_cast<uint8_t>((crc >> offset) ^ byte);
                crc = calculate_crc(crc, position);
            }
            else 
            {
                const auto position = static_cast<uint8_t>((crc >> offset) ^ detail::reflect<8>(byte));
                crc = calculate_crc(crc, position);
            }
        }
        crc = static_cast<T>(crc >> crc_offset) & mask;

        if constexpr (refout)
        {
            crc = detail::reflect<bits>(crc);
        }

        return crc ^ xor_out;
    }

    /**
     * @brief Computes CRC value of a provided string
     * 
     * @param str input string
     * @return CRC calculated for the input string
     */
    static constexpr T calculate(std::string_view str)
    {
        return calculate(DataType{reinterpret_cast<const uint8_t*>(str.data()), str.length()});
    } 

private: 
    static constexpr T calculate_crc(T crc, T position)
    {
        if constexpr (sizeof(T) == 1)
        {
            return table_[position & 0xff];
        }
        else 
        {
            return static_cast<T>((crc << 8) ^ table_[position & 0xff]);
        }
    }

    constexpr static uint32_t table_size = 256;
    using TableType = std::array<T, table_size>;

    static constexpr TableType generate_table()
    {
        TableType table{};
        for (uint64_t i = 0; i < table_size; ++i)
        {
            constexpr T mask = static_cast<T>(T(1) << (sizeof(T) * 8 - 1));
            auto remainder = static_cast<T>(i << (sizeof(T) - 1) * 8);

            for (T bit = 0; bit < 8; ++bit)
            {
                remainder = static_cast<T>((remainder & mask) != 0 ? (remainder << 1) ^ (polynomial << crc_offset) : remainder << 1);
            }
            table.at(i) = remainder;
        }
        return table;
    }
    constexpr static uint64_t crc_offset = sizeof(T) % bits != 0 ? sizeof(T) * 8 - bits : 0;
    constexpr static TableType table_ = generate_table();
};
} // namespace eul::crc
