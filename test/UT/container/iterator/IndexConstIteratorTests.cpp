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

#include "eul/container/iterator/index_const_iterator.hpp"

struct Data
{
    int value = 0;
};

struct TestingObject
{
    using value_type = Data;
    const Data& operator[](std::size_t index) const
    {
        TestingObject::index = index;
        return value;
    }

    Data value = {0};
    static std::size_t index;
};

std::size_t TestingObject::index = 0;

TEST_CASE("IndexConstIterator should", "[IndexConstIteratorTests]")
{
    using SutType = eul::container::iterator::index_const_iterator<TestingObject>;

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
        constexpr int other_test_value = 10;
        TestingObject stub{test_value};
        TestingObject::index = other_test_value;
        SutType sut(stub, 0);
        REQUIRE(stub.index == other_test_value);

        REQUIRE((*sut).value == test_value);
        REQUIRE(sut->value == test_value);
    }

    SECTION("compare iterators")
    {
        constexpr int test_value = 15;
        TestingObject stub{test_value};
        SutType sut(stub, 0);
        SutType sut2(stub, 0);
        SutType sut3(stub, 3);

        REQUIRE(sut == sut2);
        REQUIRE(sut != sut3);
        REQUIRE(sut2 != sut3);
    }
}
