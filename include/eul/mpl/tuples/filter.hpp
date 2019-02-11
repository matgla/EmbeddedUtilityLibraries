#pragma once

#include <tuple>

namespace eul
{
namespace mpl
{
namespace tuples
{
namespace detail
{
template <template <typename> typename pred, typename... T>
struct filter_impl;

template <template <typename> typename pred>
struct filter_impl<pred>
{
    using type = std::tuple<>;
};

template <typename, typename>
struct push_front;

template <typename T, typename... Rest>
struct push_front<T, std::tuple<Rest...>>
{
    using type = std::tuple<T, Rest...>;
};

template <template <typename> typename pred, typename Type, typename... Rest>
struct filter_impl<pred, Type, Rest...>
{
    using type = typename std::conditional<
        pred<Type>::value,
        typename push_front<Type,
                            typename filter_impl<pred, Rest...>::type>::type,
        typename filter_impl<pred, Rest...>::type>::type;
};
} // namespace detail

template <template <typename> typename pred, typename... Types>
struct filter
{
    using type = typename detail::filter_impl<pred, Types...>::type;
};

} // namespace tuples
} // namespace mpl
} // namespace eul
