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

#include "catch.hpp"

#include "eul/container/static_deque.hpp"

TEST_CASE("StaticDeque should", "[StaticDeque]")
{
    constexpr int value1 = 1;
    constexpr int value2 = 2;
    constexpr int value3 = 3;
    constexpr int value4 = 4;
    constexpr int value5 = 5;
    constexpr int value6 = 6;

    SECTION("not push_back elements when overflowed")
    {
        eul::container::static_deque<int, 1> sut;

        REQUIRE(sut.empty());
        REQUIRE(sut.push_back(1) == true);
        REQUIRE(sut.push_back(2) == false);
        REQUIRE(sut.size() == 1);
    }

    SECTION("not push_front elements when overflowed")
    {
        eul::container::static_deque<int, 1> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_front(2) == false);
        REQUIRE(sut.size() == 1);
    }

    SECTION("push_back elements")
    {
        eul::container::static_deque<int, 3> sut;

        REQUIRE(sut.push_back(1) == true);
        REQUIRE(sut.push_back(2) == true);
        REQUIRE(sut.push_back(3) == true);

        REQUIRE(sut[0] == 1);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 3);
        REQUIRE(sut.size() == 3);
    }

    SECTION("push_front elements")
    {
        eul::container::static_deque<int, 4> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_front(2) == true);
        REQUIRE(sut.push_front(3) == true);

        REQUIRE(sut[0] == 3);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 1);
        REQUIRE(sut.size() == 3);
    }

    SECTION("mixed push_back and front elements")
    {
        eul::container::static_deque<int, 4> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_back(2) == true);
        REQUIRE(sut.push_front(3) == true);
        REQUIRE(sut.push_back(4) == true);

        REQUIRE(sut[0] == 3);
        REQUIRE(sut[1] == 1);
        REQUIRE(sut[2] == 2);
        REQUIRE(sut[3] == 4);
        REQUIRE(sut.size() == 4);
    }

    SECTION("returns correct const iterators")
    {
        const eul::container::static_deque<int, 4> sut({1, 2, 3});

        const auto const_it = sut.begin();

        REQUIRE((*const_it) == 1);
        auto it = sut.begin();
        ++it;
        ++it;
        ++it;
        REQUIRE(sut.end() == it);
    }

    SECTION("returns correct iterators")
    {
        eul::container::static_deque<int, 4> sut({1, 2, 3});

        auto const_it = sut.begin();

        REQUIRE((*const_it) == 1);
        auto it = sut.begin();
        ++it;
        ++it;
        ++it;
        REQUIRE(sut.end() == it);
    }

    SECTION("returns max size")
    {
        eul::container::static_deque<int, 4> sut({1, 2, 3});
        REQUIRE(sut.max_size() == 4);

        constexpr std::size_t test_size = 123;
        eul::container::static_deque<int, test_size> sut2;
        REQUIRE(sut2.max_size() == test_size);
    }

    SECTION("allow front manipulations")
    {

        const eul::container::static_deque<int, 4> const_sut({value1, value2, value3});
        REQUIRE(const_sut.front() == value1);

        eul::container::static_deque<int, 4> sut({value4, value5, value6});
        REQUIRE(sut.front() == value4);
        REQUIRE(sut.pop_back());

        REQUIRE(sut.front() == value4);
        REQUIRE(sut.pop_front());

        REQUIRE(sut.front() == value5);

        REQUIRE(sut.pop_front());
        REQUIRE(sut.pop_front() == false);
    }

    SECTION("allow back manipulations")
    {
        const eul::container::static_deque<int, 4> const_sut({value1, value2, value3});
        REQUIRE(const_sut.back() == value3);
        eul::container::static_deque<int, 4> sut({value4, value5, value6});
        REQUIRE(sut.back() == value6);

        REQUIRE(sut.pop_back());
        REQUIRE(sut.back() == value5);

        REQUIRE(sut.pop_front());
        REQUIRE(sut.back() == value5);

        REQUIRE(sut.pop_back());
        REQUIRE(sut.pop_back() == false);
    }

    SECTION("Return correct empty state")
    {
        eul::container::static_deque<int, 4> sut;
        REQUIRE(sut.empty());
        sut.push_back(1);
        REQUIRE(sut.empty() == false);
    }
}
