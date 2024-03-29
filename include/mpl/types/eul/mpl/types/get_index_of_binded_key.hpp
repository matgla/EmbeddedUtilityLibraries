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

#include <cstddef>
#include <limits>
#include <tuple>

#include "eul/mpl/types/binded_traits.hpp"

namespace eul::mpl::types 
{
namespace details
{
template <typename T, int Index, typename... Args>
struct get_index_of_binded_key;

template <typename T, int Index, typename Arg, typename... Args>
struct get_index_of_binded_key<T, Index, Arg, Args...>
{
    constexpr static int get_index()
    {
        if constexpr (!is_binded<Arg>::value)
        {
            return get_index_of_binded_key<T, Index + 1, Args...>::get_index();
        }
        else if constexpr (std::is_same_v<typename Arg::KeyType, T>)
        {
            return Index;
        }
        return get_index_of_binded_key<T, Index + 1, Args...>::get_index();
    }

    constexpr static int value = get_index();
};

template <typename T, int Index>
struct get_index_of_binded_key<T, Index>
{
    constexpr static int get_index()
    {
        return -1;
    }
    constexpr static int value = get_index();
};
} // namespace details

template <typename Tuple>
struct tuple_index_getter;

template <typename... TupleArgs>
struct tuple_index_getter<std::tuple<TupleArgs...>>
{
    template <typename Key>
    constexpr static int by_key()
    {
        return details::get_index_of_binded_key<Key, 0, TupleArgs...>::value;
    }
};

template <typename Key, typename... TupleArgs>
constexpr static int get_index_from_tuple_by_key(const std::tuple<TupleArgs...>& /*unused*/)
{
    return details::get_index_of_binded_key<Key, 0, TupleArgs...>::value;
}

} // namespace eul::mpl::types
