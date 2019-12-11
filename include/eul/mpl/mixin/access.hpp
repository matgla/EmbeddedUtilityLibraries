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
#include "eul/mpl/mixin/name.hpp"
#include "eul/mpl/tuples/filter.hpp"
#include "eul/mpl/tuples/for_each.hpp"
#include "eul/mpl/types/bind_type.hpp"
#include "eul/mpl/types/binded_traits.hpp"
#include "eul/mpl/types/get_index_of_binded_key.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename MixedObject>
struct access
{
    constexpr access(void* data)
        : object_(*static_cast<MixedObject*>(data))
    {
    }

    template <template <typename> typename Ability>
    auto& get_by_ability()
    {
        return std::get<ability_to_index<Ability, decltype(object_.data_)>::value>(object_.data_);
    }

    template <template <typename> typename T>
    auto& operator[](ability<T>)
    {
        return get_by_ability<T>();
    }

    template <typename DataType>
    DataType& get()
    {
        return std::get<DataType>(object_.data_);
    }

    template <typename T>
    auto& operator[](type<T>)
    {
        return get<T>();
    }

    template <typename Name>
    auto& get_by_name()
    {
        using TupleType                   = decltype(object_.data_);
        constexpr std::size_t indexOfType = types::tuple_index_getter<TupleType>::template by_key<Name>();
        return std::get<indexOfType>(object_.data_);
    }

    template <typename Name>
    static auto constexpr get_binded()
    {
        using TupleType                   = typename MixedObject::DataType;
        constexpr std::size_t indexOfType = types::tuple_index_getter<TupleType>::template by_key<Name>();
        using ElementType                 = typename std::tuple_element<indexOfType, TupleType>::type;
        return types::binded<Name, ElementType>{};
    }

    template <typename Name>
    auto& operator[](name<Name>)
    {
        return get_by_name<Name>().value;
    }

    template <template <typename> typename Predicate, typename Functor>
    void for_each(ability<Predicate>, Functor f)
    {
        tuples::for_each<Predicate, decltype(object_.data_)>(object_.data_, f);
    }

private:
    MixedObject& object_;
};

} // namespace mixin
} // namespace mpl
} // namespace eul
