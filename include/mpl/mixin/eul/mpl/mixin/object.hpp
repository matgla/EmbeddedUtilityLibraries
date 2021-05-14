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

#include "eul/mpl/mixin/access.hpp"
#include "eul/mpl/mixin/inherit_from.hpp"
#include "eul/mpl/mixin/interface.hpp"
#include "eul/mpl/mixin/type.hpp"
#include "eul/mpl/tuples/filter.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename Interface, typename... Datas>
struct object : public inherit_from<object<Interface, Datas...>, Interface>
{
public:
    template <template <typename> typename... Interfaces>
    constexpr object(interface<Interfaces...>, Datas&&... args)
        : data_(std::forward<Datas>(args)...)
    {
    }

    using DataType = std::tuple<Datas...>;
    DataType data_;

    friend class eul::mpl::mixin::access<object>;
};

template <template <typename> typename... Interfaces, typename... Datas>
object(interface<Interfaces...>, Datas...)->object<interface<Interfaces...>::template type, Datas...>;

} // namespace mixin
} // namespace mpl
} // namespace eul
