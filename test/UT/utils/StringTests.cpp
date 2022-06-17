// This file is part of EUL project. This project is set of libraries useful for embedded development.
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

#include <string_view>
#include <span>

#include <catch2/catch_test_macros.hpp>

#include <eul/utils/string.hpp>

namespace eul::utils
{
    
TEST_CASE("StringUtilsShould", "[UtilsTests]")
{
    SECTION("ConvertIntegersToString")
    {
        constexpr int data_0 = 0;
        constexpr int data_1 = 12345;
        constexpr int data_2 = -6789999;

        char buffer[255];
        itoa<10>(data_0, buffer);
        REQUIRE(std::string_view{buffer} == "0");
        itoa(data_1, buffer);
        REQUIRE(std::string_view{buffer} == "12345");
        itoa<10>(data_2, buffer);
        REQUIRE(std::string_view{buffer} == "-6789999");

        itoa<8>(data_0, buffer);
        REQUIRE(std::string_view{buffer} == "0");
        itoa<8>(data_1, buffer);
        REQUIRE(std::string_view{buffer} == "30071");
        itoa<8>(data_2, buffer);
        REQUIRE(std::string_view{buffer} == "-31715557");

        itoa<16>(data_0, buffer);
        REQUIRE(std::string_view{buffer} == "0");
        itoa<16>(data_1, buffer);
        REQUIRE(std::string_view{buffer} == "3039");
        itoa<16>(data_2, buffer);
        REQUIRE(std::string_view{buffer} == "-679b6f");
    }
    SECTION("Convert single digit to char")
    {
        REQUIRE(int_to_char(0) == '0');
        REQUIRE(int_to_char(1) == '1');
        REQUIRE(int_to_char(2) == '2');
        REQUIRE(int_to_char(3) == '3');
        REQUIRE(int_to_char(4) == '4');
        REQUIRE(int_to_char(5) == '5');
        REQUIRE(int_to_char(6) == '6');
        REQUIRE(int_to_char(7) == '7');
        REQUIRE(int_to_char(8) == '8');
        REQUIRE(int_to_char(9) == '9');
        REQUIRE(int_to_char(10) == 'a');
        REQUIRE(int_to_char(11) == 'b');
        REQUIRE(int_to_char(12) == 'c');
        REQUIRE(int_to_char(13) == 'd');
        REQUIRE(int_to_char(14) == 'e');
        REQUIRE(int_to_char(15) == 'f');
    }
    SECTION("Calculate string length")
    {
        int data_0[] = {'a', 'b', 'c', 0, 'a'};
        char data_1[] = {'b', 'c', 0, 'b'};

        REQUIRE(eul::utils::strlen(std::span(data_0, 5)) == 3);
        REQUIRE(eul::utils::strlen(std::span(data_1, 4)) == 2);
    }
}

} // namespace eul::utils

