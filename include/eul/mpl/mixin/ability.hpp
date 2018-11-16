#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/mixin/type.hpp"

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

template <template <typename> typename Ability, std::size_t Index,
          typename... Args>
struct ability_to_index_impl;

template <std::size_t ArgsSize, template <typename> typename Ability,
          typename Args>
constexpr bool not_last_arg_without_ability()
{
    if constexpr (ArgsSize != 0)
    {
        return true;
    }

    return Ability<Args>::value;
}

template <template <typename> typename Ability, std::size_t Index>
struct ability_to_index_impl<Ability, Index>
{
    static_assert(Index != 0, "Any data in mixed object");

    constexpr static std::size_t value = -1;
};


template <template <typename> typename Ability, std::size_t Index, typename Arg,
          typename... Args>
struct ability_to_index_impl<Ability, Index, Arg, Args...>
{
    static_assert(not_last_arg_without_ability<sizeof...(Args), Ability, Arg>(),
                  "Data with specified ability not exists");
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

} // namespace mixin
} // namespace mpl
} // namespace eul
