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

#include <array>

#include <catch.hpp>

#include <eul/crc/crc.hpp>

TEST_CASE("Crc32Tests", "[CRC_TESTS]")
{
    SECTION("Calculate correctly CRC32 for default polynomial")
    {
        std::array<uint8_t, 3> data = {0x00, 0x12, 0x00};
        REQUIRE(0x87b5a9c1 == calculate_crc32(data));

        data[1] = 0x00;
        REQUIRE(0xff41d912 == calculate_crc32(data));

        std::array<uint8_t, 5> data2 = {0xff, 0xff, 0xff, 0xff, 0xff};
        REQUIRE(0xd2fd1072 == calculate_crc32(data2));
    }
    SECTION("Calculate correctly CRC8 for default polynomial")
    {
        std::array<uint8_t, 3> data = {0x2, 0x3, 0xff};
        REQUIRE(0x1a == calculate_crc8(data));

        data[1] = 0xff;
        REQUIRE(0xf2 == calculate_crc8(data));
        std::array<uint8_t, 4> data2 = {0xff, 0xff, 0xff, 0xff};
        REQUIRE(0xde == calculate_crc8(data2));
    }
    SECTION("Calculate correctly CRC16-CCIT") 
    {
        std::array<uint8_t, 3> data = {0x2, 0x3, 0xff};
        REQUIRE(0x25c3 == calculate_crc16<ccit_polynomial>(data));

        data[1] = 0xff;
        REQUIRE(0x736f == calculate_crc16<ccit_polynomial>(data));
        std::array<uint8_t, 4> data2 = {0xff, 0xff, 0xff, 0xff};
        REQUIRE(0x99cf == calculate_crc16<ccit_polynomial>(data2));
    }

}
