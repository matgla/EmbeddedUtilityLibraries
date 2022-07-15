//! [Doxygen CRC example - source]
/*
 Copyright (c) 2022 Mateusz Stadnik

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <eul/crc/crc32.hpp>
#include <eul/crc/crc4.hpp>
#include <eul/crc/crc8.hpp>

#include <array>
#include <cstdint>
#include <iostream>
#include <string_view>

int main()
{
    constexpr std::array<uint8_t, 9> data{0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
    constexpr std::string_view string = "123456789";

    std::cout << "Crc8     : 0x" << std::hex << +eul::crc::Crc8::calculate(data) << std::endl;
    std::cout << "Crc32    : 0x" << std::hex << eul::crc::Crc32::calculate(data) << std::endl;
    std::cout << "Crc4_ITU : 0x" << std::hex << +eul::crc::Crc4_ITU::calculate(string) << std::endl;
}

//! [Doxygen CRC example - source]