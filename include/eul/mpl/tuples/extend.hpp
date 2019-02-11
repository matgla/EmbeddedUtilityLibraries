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
