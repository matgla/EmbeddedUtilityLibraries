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

#include <catch2/catch_test_macros.hpp>

#include "eul/container/iterator/index_iterator.hpp"

struct Data
{
    int value = 0;
};

struct TestingObject
{
    using value_type = Data;
    Data& operator[](std::size_t i)
    {
        this->index = i;
        return value;
    }

    Data value        = {0};
    std::size_t index = 0;
};

TEST_CASE("IndexIterator should", "[IndexIteratorTests]")
{
    using SutType = eul::container::iterator::index_iterator<TestingObject>;

    SECTION("PostIncrement")
    {
        TestingObject stub;
        SutType sut(stub, 0);
        *sut;
        REQUIRE(stub.index == 0);

        auto it = sut++;
        *sut;
        REQUIRE(stub.index == 1);
        *it;
        REQUIRE(stub.index == 0);
    }

    SECTION("PreIncrement")
    {
        TestingObject stub;
        SutType sut(stub, 0);
        *sut;
        REQUIRE(stub.index == 0);

        auto it = ++sut;
        *sut;
        REQUIRE(stub.index == 1);
        *it;
        REQUIRE(stub.index == 1);
    }

    SECTION("Access value")
    {
        constexpr int test_value = 15;
        constexpr int test_index = 10;
        TestingObject stub{{test_value}, test_index};
        SutType sut(stub, 0);
        REQUIRE(stub.index == test_index);

        REQUIRE((*sut).value == test_value);
        REQUIRE(sut->value == test_value);
    }

    SECTION("compare iterators")
    {
        constexpr int test_value = 15;
        constexpr int test_index = 10;
        TestingObject stub{{test_value}, test_index};
        SutType sut(stub, 0);
        SutType sut2(stub, 0);
        SutType sut3(stub, 3);

        REQUIRE(sut == sut2);
        REQUIRE(sut != sut3);
        REQUIRE(sut2 != sut3);
    }
}
