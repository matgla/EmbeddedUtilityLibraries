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

#include <string>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include "eul/mpl/types/bind_type.hpp"
#include "eul/mpl/types/get_index_of_binded_key.hpp"

namespace eul::mpl::types
{

TEST_CASE("GetIndexOfBindedKey should", "[GetIndexOfBindedKey]")
{
    SECTION("Get index of binded key in tuple")
    {
        class A;
        class AI{};

        class B;
        class BI{};

        class C;
        class CI{};

        auto binded = std::make_tuple(
            bind_type<A>::to(AI{}),
            bind_type<B>::to(BI{}),
            bind_type<C>::to(CI{}));

        class D;

        using BindedType = decltype(binded);

        REQUIRE(tuple_index_getter<BindedType>::by_key<A>() == 0);
        REQUIRE(tuple_index_getter<BindedType>::by_key<B>() == 1);
        REQUIRE(tuple_index_getter<BindedType>::by_key<C>() == 2);

        REQUIRE(std::tuple_size<BindedType>::value == 3);
        REQUIRE(tuple_index_getter<BindedType>::by_key<D>() == -1);

        REQUIRE(get_index_from_tuple_by_key<A>(binded) == 0);
        REQUIRE(get_index_from_tuple_by_key<B>(binded) == 1);
        REQUIRE(get_index_from_tuple_by_key<C>(binded) == 2);

        REQUIRE(std::tuple_size<BindedType>::value == 3);
        REQUIRE(get_index_from_tuple_by_key<D>(binded) == -1);
    }
}

} // namespace eul::mpl::types
