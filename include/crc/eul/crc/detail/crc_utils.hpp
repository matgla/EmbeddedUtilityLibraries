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
#include <tuple> 

namespace eul::crc::detail
{
    constexpr static std::array<uint8_t, 16> reflect_lookup = {
        0b0000, 0b1000, 0b0100, 0b1100,
        0b0010, 0b1010, 0b0110, 0b1110,
        0b0001, 0b1001, 0b0101, 0b1101,
        0b0011, 0b1011, 0b0111, 0b1111
    };

    template <std::size_t bits>
    constexpr uint8_t reflect_impl(const uint8_t byte)
    {
        static_assert(bits <= 8, "Bits must be less than 9");
        if constexpr (bits == 0)
        {
            return 0;
        }
        else 
        {
            constexpr std::size_t offset = sizeof(uint8_t) * 8 - bits;
            return static_cast<uint8_t>((reflect_lookup[(byte >> 4u) & 0xfu] // NOLINT (cppcoreguidelines-pro-bounds-constant-array-index)
                | (reflect_lookup[byte & 0xfu] << 4u)) >> offset); // NOLINT (cppcoreguidelines-pro-bounds-constant-array-index)
        }

    }

    template <std::size_t bits>
    constexpr uint16_t reflect_impl(const uint16_t data) 
    {
        static_assert(bits <= 16, "Bits must be less than 17");
        if constexpr (bits <= 8)
        {
            return reflect_impl<bits>(static_cast<uint8_t>(data));
        }
        else 
        {
            constexpr std::size_t offset = bits - 8;

            return static_cast<uint16_t>(
                reflect_impl<8>(static_cast<uint8_t>(data)) << offset
                | reflect_impl<offset>(static_cast<uint8_t>(data >> 8))
            );
        }
    }

    template <std::size_t bits>
    constexpr uint32_t reflect_impl(const uint32_t data)
    {
        static_assert(bits <= 32, "Bits must be less than 33");

        if constexpr (bits <= 16)
        {
            return reflect_impl<bits>(static_cast<uint16_t>(data));
        }
        else 
        {
            return static_cast<uint32_t>(
                reflect_impl<16>(static_cast<uint16_t>(data)) << (bits - 16)
                | reflect_impl<bits - 16>(static_cast<uint16_t>(data >> 16))
            );
        }

    }

    template <std::size_t bits>
    constexpr uint64_t reflect_impl(const uint64_t data)
    {
        static_assert(bits <= 64, "Bits must be less than 65");
        if constexpr (bits <= 32)
        {
            return reflect_impl<bits>(static_cast<uint32_t>(data));
        }
        else 
        {
            return static_cast<uint64_t>(
                static_cast<uint64_t>(reflect_impl<32>(static_cast<uint32_t>(data))) << (bits - 32)
                 | static_cast<uint64_t>(reflect_impl<bits - 32>(static_cast<uint32_t>(data >> 32)))
            );
        }
    }

    using Types = std::tuple<uint8_t, uint16_t, uint32_t, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t>;

    template <std::size_t bits>
    struct deduce_type_from_size 
    {
        static_assert(bits > 0 && bits <= 64, "Bits must be greater than 0 and less than 65");
        using type = std::tuple_element_t<(bits-1)/8, Types>;
    };


    template <std::size_t bits> 
    constexpr typename deduce_type_from_size<bits>::type reflect(const auto data)  
    {
        static_assert (bits > 0 && bits <= 64, "Bits must be greater than 0 and less than 65");
        return reflect_impl<bits>(static_cast<typename deduce_type_from_size<bits>::type>(data));
    }
} // namespace eul::crc::detail

