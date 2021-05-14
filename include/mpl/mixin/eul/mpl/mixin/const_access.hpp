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

#include "eul/mpl/mixin/ability.hpp"
#include "eul/mpl/mixin/access.hpp"
#include "eul/mpl/mixin/data.hpp"
#include "eul/mpl/tuples/for_each.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename MixedObject>
struct const_access
{
    constexpr const_access(const void* data) : object_(*static_cast<const MixedObject*>(data))
    {
    }

    template <typename DataType>
    const DataType& get() const
    {
        return std::get<DataType>(object_.data_);
    }

    template <template <typename> typename Ability>
    const auto& get_by_ability() const 
    {
        return std::get<
            ability_to_index<Ability, decltype(object_.data_)>::value>(
            object_.data_);
    }

    template <template <typename> typename T>
    const auto& operator[](ability<T>) const
    {
        return get_by_ability<T>();
    }

    template <typename T>
    const auto& operator[](type<T>) const
    {
        return get<T>();
    }

    template <template <typename> typename Predicate, typename Functor>
    void for_each(ability<Predicate>, Functor f) const
    {
        tuples::for_each<Predicate, decltype(object_.data_)>(object_.data_, f);
    }

private:
    const MixedObject& object_;
};

} // namespace mixin
} // namespace mpl
} // namespace eul
