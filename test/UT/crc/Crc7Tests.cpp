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

#include <catch2/catch_test_macros.hpp>

#include <eul/crc/crc.hpp>

TEST_CASE("Crc7Tests", "[CRC_TESTS]")
{
    SECTION("Calculate correctly CRC7 for default polynomial")
    {
        std::array<uint8_t, 3> data = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
        REQUIRE(0x87b5a9c1 == calculate_crc32(data));

        data[1] = 0x00;
        REQUIRE(0xff41d912 == calculate_crc32(data));

        std::array<uint8_t, 5> data2 = {0xff, 0xff, 0xff, 0xff, 0xff};
        REQUIRE(0xd2fd1072 == calculate_crc32(data2));
    }
}
