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

namespace eul
{
namespace mpl
{
namespace tuples
{
namespace detail
{
template <template <typename> typename pred, typename... T>
struct filter_impl;

template <template <typename> typename pred>
struct filter_impl<pred>
{
    using type = std::tuple<>;
};

template <typename, typename>
struct push_front;

template <typename T, typename... Rest>
struct push_front<T, std::tuple<Rest...>>
{
    using type = std::tuple<T, Rest...>;
};

template <template <typename> typename pred, typename Type, typename... Rest>
struct filter_impl<pred, Type, Rest...>
{
    using type = typename std::conditional<
        pred<Type>::value,
        typename push_front<Type,
                            typename filter_impl<pred, Rest...>::type>::type,
        typename filter_impl<pred, Rest...>::type>::type;
};
} // namespace detail

template <template <typename> typename pred, typename... Types>
struct filter
{
    using type = typename detail::filter_impl<pred, Types...>::type;
};

} // namespace tuples
} // namespace mpl
} // namespace eul
