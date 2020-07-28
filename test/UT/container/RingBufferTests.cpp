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

#include <catch.hpp>

#include "eul/container/ring_buffer.hpp"


TEST_CASE("Ring buffer should", "[RingBufferTests]")
{
    SECTION("push elements")
    {
        eul::container::ring_buffer<int, 4> sut;

        REQUIRE(sut.empty());
        sut.push(1);
        sut.push(2);
        sut.push(3);
        sut.push(4);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut.pop() == 1);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 2);
        REQUIRE(sut.pop() == 3);
        REQUIRE(sut.pop() == 4);
        REQUIRE(sut.empty());
    }

    SECTION("push override elements")
    {
        eul::container::ring_buffer<int, 3> sut;

        constexpr int value_1 = 1;
        constexpr int value_2 = 2;
        constexpr int value_3 = 3;
        constexpr int value_4 = 4;
        constexpr int value_5 = 5;
        constexpr int value_6 = 7;
        constexpr int value_7 = 8;
        constexpr int value_8 = 9;
        constexpr int value_9 = 10;
        constexpr int value_10 = 11;
        constexpr int value_11 = 12;
        constexpr int value_12 = 13;
        constexpr int value_13 = 14;

        REQUIRE(sut.empty());
        sut.push(value_1);
        sut.push(value_2);
        sut.push(value_3);
        sut.push(value_4);
        sut.push(value_5);

        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == value_3);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.pop() == value_4);
        REQUIRE(sut.pop() == value_5);
        REQUIRE(sut.empty());

        sut.push(value_5);
        sut.push(value_6);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.pop() == value_5);
        REQUIRE(sut.size() == 1);

        sut.push(value_7);
        sut.push(value_8);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == value_6);
        REQUIRE(sut.size() == 2);

        sut.push(value_9);
        sut.push(value_10);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == value_8);
        REQUIRE(sut.size() == 2);

        sut.push(value_11);
        sut.push(value_12);
        sut.push(value_13);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == value_11);
        REQUIRE(sut.size() == 2);
    }

    SECTION("return front element")
    {
        eul::container::ring_buffer<int, 3> sut;

        constexpr int value_1 = 1;
        constexpr int value_2 = 2;
        constexpr int value_3 = 3;
        constexpr int value_4 = 4;
        constexpr int value_5 = 5;

        REQUIRE(sut.empty());
        sut.push(value_1);
        sut.push(value_2);
        sut.push(value_3);
        sut.push(value_4);
        sut.push(value_5);

        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front() == value_3);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front() == value_3);

        REQUIRE(sut.pop() == value_3);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front() == value_4);
        REQUIRE(sut.size() == 2);
    }
}
