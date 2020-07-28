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

#include <cstdint>
#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/tuples/extend.hpp"

namespace eul::mpl::tuples
{

TEST_CASE("Extend should", "[AddType]")
{
    SECTION("extend types")
    {
        using TwoTypesTuple = extend<std::tuple<int>>::with<double>::type;
        using FiveTypesTuple = extend<TwoTypesTuple>::with<double, char, std::int64_t>::type;

        REQUIRE(std::tuple_size<TwoTypesTuple>::value == 2);
        REQUIRE(std::tuple_size<FiveTypesTuple>::value == 5);
        REQUIRE(typeid(TwoTypesTuple).name()
                == typeid(std::tuple<int, double>).name());
        REQUIRE(typeid(FiveTypesTuple).name()
                == typeid(std::tuple<int, double, double, char, std::int64_t>).name());
    }
}

} // namespace eul::mpl::tuples
