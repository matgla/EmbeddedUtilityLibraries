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
struct access
{
    constexpr access(void* data) : object_(*static_cast<MixedObject*>(data))
    {
    }

    template <typename DataType>
    DataType& get()
    {
        return std::get<DataType>(object_.data_);
    }

    template <template <typename> typename Ability>
    auto& get_by_ability()
    {
        return std::get<
            ability_to_index<Ability, decltype(object_.data_)>::value>(
            object_.data_);
    }

    template <template <typename> typename T>
    auto& operator[](ability<T>)
    {
        return get_by_ability<T>();
    }

    template <typename T>
    auto& operator[](type<T>)
    {
        return get<T>();
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
