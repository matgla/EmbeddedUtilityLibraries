// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
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

#include "catch2/catch_test_macros.hpp"

#include "eul/memory/observer.hpp"
#include "eul/utils/unused.hpp"

TEST_CASE("Observer should", "[Observer]")
{
    SECTION("Forward calls")
    {
        int int_called_with       = 0;
        bool custom_called        = false;
        double double_called_with = 0.0;

        struct Custom
        {
        };

        eul::Observer observer{
            [&int_called_with](const int i) { int_called_with = i; },
            [&double_called_with](const double d) { double_called_with = d; },
            [&custom_called](const Custom& c) { UNUSED1(c); custom_called = true; }};

        constexpr int some_integer = 123;
        constexpr double some_floating = 432.123;
        observer(some_integer);
        observer(Custom{});
        observer(some_floating);

        REQUIRE(int_called_with == some_integer);
        REQUIRE(double_called_with == some_floating);
        REQUIRE(custom_called);
    }
}
