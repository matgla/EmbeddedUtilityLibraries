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

#include "eul/mpl/tuples/filter.hpp"

namespace eul
{
namespace mpl
{
namespace tuples
{

template <typename... T>
struct interface
{
    using Type = std::tuple<T...>;
};

struct WithInterface
{
};

struct WithInterface2
{
};

struct WithoutInterface
{
};

template <typename T>
struct is_interface : std::false_type
{
};


template <typename... T>
struct is_interface<interface<T...>> : std::true_type
{
};


TEST_CASE("Filter should", "[Filter]")
{
    SECTION("filter integers")
    {
        using IntegerTuple = typename filter<std::is_integral, int, long double,
                                             std::string, long int>::type;

        REQUIRE(std::tuple_size<IntegerTuple>::value == 2);
        REQUIRE(typeid(IntegerTuple).name()
                == typeid(std::tuple<int, long int>).name());
    }

    SECTION("filter by own predicate")
    {
        using Interfaces =
            typename filter<is_interface, interface<WithInterface>,
                            interface<WithInterface>, interface<WithInterface2>,
                            WithInterface, WithoutInterface>::type;

        REQUIRE(typeid(Interfaces).name()
                == typeid(std::tuple<interface<WithInterface>,
                                     interface<WithInterface>,
                                     interface<WithInterface2>>)
                       .name());
    }
}

} // namespace tuples
} // namespace mpl
} // namespace eul
