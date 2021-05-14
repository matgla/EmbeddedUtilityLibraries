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
namespace details
{

template <typename... Types>
struct extended_tuple
{
    using type = std::tuple<Types...>;
};

} // namespace details

template <typename T>
struct extend;

template <typename... Args>
struct extend<std::tuple<Args...>>
{
    using type = std::tuple<Args...>;
    template <typename... NewTypes>
    using with = details::extended_tuple<Args..., NewTypes...>;
};

} // namespace tuples
} // namespace mpl
} // namespace eul
