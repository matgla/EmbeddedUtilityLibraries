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
namespace mixin
{

template <typename... T>
struct interface_t : public T...
{
};


template <template <typename> typename... Ts>
struct interface
{
    template <typename T>
    using type = interface_t<Ts<T>...>;
};

template <typename T>
struct is_interface : std::false_type
{
};

template <typename T>
struct is_interface<interface_t<T>> : std::true_type
{
};

template <typename T>
struct is_not_interface : std::true_type
{
};

template <typename T>
struct is_not_interface<interface_t<T>> : std::false_type
{
};

} // namespace mixin
} // namespace mpl
} // namespace eul
