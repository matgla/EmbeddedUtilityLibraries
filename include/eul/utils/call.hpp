#pragma once

namespace eul
{
namespace utils
{

template <class R, class... Ts>
auto call_impl(R (*f)(Ts...))
{
    return [f](Ts... args)
    {
        return f(args...);
    };
}
template <class T, class R, class... Ts>
auto call_impl(T* self, R (T::*f)(Ts...))
{
    return [self, f](Ts... args)
    {
        return (self->*f)(args...);
    };
}
template <class T, class R, class... Ts>
auto call_impl(const T* self, R (T::*f)(Ts...) const)
{
    return [self, f](Ts... args)
    {
        return (self->*f)(args...);
    };
}
template <class T, class R, class... Ts>
auto call_impl(const T* self, R (T::*f)(Ts...))
{
    return [self, f](Ts... args)
    {
        return (self->*f)(args...);
    };
}

auto call = [](auto... args)
{
    return call_impl(args...);
};

} // namespace utils
} // namespace eul
