#pragma once

#include <string_view>
#include <type_traits>

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

// clang-format off

template <typename T>
struct is_logger : std::false_type {};

template <typename T>
concept bool LoggerInterface = requires(T a)
{
    { a.debug() } -> LoggerInterface;
    { a.info() } -> LoggerInterface;
    { a.warning() } -> LoggerInterface;
    { a.error() } -> LoggerInterface;
    { a.trace() } -> LoggerInterface;
    { a << "some data"} -> LoggerInterface&;
    { a << 1234 } -> LoggerInterface&;
};

template <LoggerInterface T>
struct is_logger<T> : std::true_type {};

// clang-format on

} // namespace logger
} // namespace eul
