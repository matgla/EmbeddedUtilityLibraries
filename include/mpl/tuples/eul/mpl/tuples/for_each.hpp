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

#pragma once

#include <tuple>
#include <type_traits>

namespace eul
{
namespace mpl
{
namespace tuples
{
namespace detail
{

template <typename Tuple, std::size_t Index, typename Fn>
constexpr void for_each_impl(const Fn& fn, Tuple& tuple)
{
    fn(std::get<Index>(tuple));
    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Tuple, Index + 1, Fn>(fn, tuple);
    }
}

template <template <typename> typename Pred, typename Tuple, std::size_t Index, typename Fn>
constexpr void for_each_impl(const Fn& fn, Tuple& tuple)
{
    if constexpr (Pred<typename std::tuple_element<Index, Tuple>::type>::value)
    {
        fn(std::get<Index>(tuple));
    }

    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Pred, Tuple, Index + 1, Fn>(fn, tuple);
    }
}

} // namespace detail

template <typename Tuple, typename Fn, std::size_t Size = 0>
constexpr void for_each(Tuple& t, const Fn& fn)
{
    detail::for_each_impl<Tuple, 0, Fn>(fn, t);
}

template <template <typename> typename Pred, typename Tuple, typename Fn>
constexpr void for_each(Tuple& t, const Fn& fn)
{
    detail::for_each_impl<Pred, Tuple, Fn, 0>(fn, t);
}

} // namespace tuples
} // namespace mpl
} // namespace eul
