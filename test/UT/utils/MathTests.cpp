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

#include <eul/utils/math.hpp>

namespace eul::utils
{
    
TEST_CASE("MathUtilsShould", "[MathTests]")
{
    SECTION("Calculate power")
    {
        REQUIRE(pow(1, 100) == 1);
        REQUIRE(pow(2, 4) == 16);
        REQUIRE(pow(3, 3) == 27);
    }

    SECTION("Convert floats to int pair")
    {
        const auto [integer, fractal] = floatToInts(1234.5678f, 2);
        REQUIRE(integer == 1234);
        REQUIRE(fractal == 57);

        const auto [integer1, fractal1] = floatToInts(1234.56781f, 4);
        REQUIRE(integer1 == 1234);
        REQUIRE(fractal1 == 5677);

        const auto [integer2, fractal2] = floatToInts(0.12f, 4);
        REQUIRE(integer2 == 0);
        REQUIRE(fractal2 == 1200);
    }
}

} // namespace eul::utils

