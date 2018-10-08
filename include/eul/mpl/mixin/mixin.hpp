#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/filter.hpp"
#include "eul/mpl/inherit_from.hpp"
#include "eul/mpl/mixin/interface.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename Predicate>
struct ability
{
};

template <typename Type>
struct type
{
};


template <template <typename> typename Ability, std::size_t Index,
          typename... Args>
struct ability_to_index_impl;


template <template <typename> typename Ability, std::size_t Index>
struct ability_to_index_impl<Ability, Index>
{
    constexpr static std::size_t value = -1;
};

template <template <typename> typename Ability, std::size_t Index, typename Arg,
          typename... Args>
struct ability_to_index_impl<Ability, Index, Arg, Args...>
{
    static_assert(Ability<Arg>::value, "type");
    constexpr static std::size_t value
        = Ability<Arg>::value == true
              ? Index
              : ability_to_index_impl<Ability, Index + 1, Args...>::value;
};

template <template <typename> typename Ability, typename... Args>
struct ability_to_index;

template <template <typename> typename Ability, typename... Args>
struct ability_to_index<Ability, std::tuple<Args...>>
{
    constexpr static std::size_t value
        = ability_to_index_impl<Ability, 0, Args...>::value;
};

template <template <typename> typename Pred, typename Tuple, std::size_t Index>
constexpr void for_each_impl(const auto& fn, Tuple& tuple)
{
    if constexpr (Pred<typename std::tuple_element<Index, Tuple>::type>::value)
    {
        fn(std::get<Index>(tuple));
    }

    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Pred, Tuple, Index + 1>(fn, tuple);
    }
}

template <template <typename> typename Pred, typename Tuple>
constexpr void for_each(Tuple& t, const auto& fn)
{
    for_each_impl<Pred, Tuple, 0>(fn, t);
}

template <typename MixedObject>
struct access
{
    constexpr access(void* data) : object_(*static_cast<MixedObject*>(data))
    {
    }

    template <typename DataType>
    DataType& get()
    {
        return std::get<data_t<DataType>>(object_.data_);
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
        mixin::for_each<Predicate, decltype(object_.data_)>(object_.data_, f);
    }

private:
    MixedObject& object_;
};


template <template <typename> typename... Types>
struct mixin
    : public inherit_from<
          typename filter<is_interface, Types<mixin<Types...>>...>::type>
{
public:
    using DataType = typename filter<is_data, Types<mixin<Types...>>...>::type;
    DataType data_;

    friend class access<mixin>;
};

} // namespace mixin
} // namespace mpl
} // namespace eul
