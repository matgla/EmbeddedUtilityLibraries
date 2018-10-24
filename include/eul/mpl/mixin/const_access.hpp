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
