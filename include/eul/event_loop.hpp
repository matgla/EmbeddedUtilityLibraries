#pragma once

#include <tuple>

#include "eul/function.hpp"


namespace eul
{
namespace detail
{
template <std::size_t, typename T>
struct Convert;

template <std::size_t CallbackSize, typename T>
struct Convert
{
    using Type = function<void(const T&), CallbackSize>;
};

template <std::size_t, typename... Args>
struct Binder;

template <std::size_t CallbackSize, typename... Args>
struct Binder<CallbackSize, std::tuple<Args...>>
{
    typedef std::tuple<typename Convert<CallbackSize, Args>::Type...> type;
};
} // namespace detail

template <std::size_t CallbackSize, typename... Events>
class event_loop
{
public:
    template <typename EventType>
    using CallbackType = function<void(const EventType&), CallbackSize>;

    template <typename EventType>
    void registerEvent(const CallbackType<EventType>& callback)
    {
        std::get<CallbackType<EventType>>(callbacks_) = callback;
    }

    template <typename EventType>
    constexpr void dispatch(const EventType& event)
    {
        if (!std::get<CallbackType<EventType>>(callbacks_))
        {
            return;
        }
        std::get<CallbackType<EventType>>(callbacks_)(event);
    }

    template <typename EventType>
    constexpr void unregister()
    {
        std::get<CallbackType<EventType>>(callbacks_) = nullptr;
    }

private:
    typename detail::Binder<CallbackSize, std::tuple<Events...>>::type callbacks_;
};

} // namespace eul
