#pragma once

#include <type_traits>

#include "eul/mpl/types/bind_type.hpp"

namespace eul
{
namespace mpl
{
namespace types
{

template <typename... T>
struct is_binded : public std::false_type
{};

template <typename Key, typename Value>
struct is_binded<binded<Key, Value>> : public std::true_type
{};

} // namespace types
} // namespace mpl
} // namespace eul
