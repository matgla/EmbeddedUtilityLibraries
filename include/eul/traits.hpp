#pragma once

#include <string>
#include <tuple>
#include <type_traits>

namespace eul
{
template <typename Tuple, typename Type>
struct has_type;

template <typename Type, typename... Args>
struct has_type<std::tuple<Args...>, Type>
    : std::disjunction<std::is_same<Type, Args>...>
{
};

struct pointer_size
{
    constexpr static std::size_t size = sizeof(void*);
};

} // namespace eul
