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

#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/mixin/inherit_from.hpp"

namespace eul::mpl::mixin
{

template <typename ParentType>
struct ChildOne
{
public:
    static constexpr int value()
    {
        return 1;
    }
};

template <typename ParentType>
struct ChildTwo
{
public:
    static constexpr int someNumber()
    {
        constexpr int some_number = 10;
        return some_number;
    }
};

TEST_CASE("InheritFrom should", "[InheritFrom]")
{
    SECTION("Inherit from one type")
    {
        struct Parent : public eul::mpl::mixin::inherit_from<Parent, ChildOne>
        {
        };
        Parent p;

        REQUIRE(p.value() == 1);
    }

    SECTION("Inherit from multiple types")
    {
        struct Parent
            : public eul::mpl::mixin::inherit_from<Parent, ChildOne, ChildTwo>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }

    SECTION("inherit from tuple")
    {
        struct Parent : public eul::mpl::mixin::inherit_from<
                            std::tuple<ChildOne<Parent>, ChildTwo<Parent>>>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }
}

} // namespace eul::mpl::mixin
