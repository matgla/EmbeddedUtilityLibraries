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
        using TupleType = decltype(object_.data_);
        constexpr std::size_t indexOfType
            = types::tuple_index_getter<TupleType>::template by_key<Name>();
        return std::get<indexOfType>(object_.data_);
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
