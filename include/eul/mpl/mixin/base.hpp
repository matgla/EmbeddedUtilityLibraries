#pragma once

#include <tuple>
#include <type_traits>

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename... T>
struct base_t : public T...
{
};


template <template <typename> typename... Ts>
struct base
{
    template <typename T>
    using type = base_t<Ts<T>...>;
};

template <typename T>
struct is_base : std::false_type
{
};

template <typename T>
struct is_base<base_t<T>> : std::true_type
{
};

template <typename T>
struct is_not_base : std::true_type
{
};

template <typename T>
struct is_not_base<base_t<T>> : std::false_type
{
};

} // namespace mixin
} // namespace mpl
} // namespace eul
