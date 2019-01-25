#pragma once

#include <string_view>

namespace eul
{
namespace logger
{

// clang-format off
template <typename T>
concept bool Writable = requires(T a)
{
    { a.write(std::string_view{}) } -> void;
};
// clang-format on

} // namespace logger
} // namespace eul
