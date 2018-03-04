#pragma once

#include <tuple>

#include "eul/function.hpp"


namespace eul
{
namespace detail
{
template <std::size_t, typename T>
struct convert;

template <std::size_t CallbackSize, typename T>
struct convert
{
    using callback_type = function<void(const T&), CallbackSize>;
};

template <std::size_t, typename... Args>
struct binder;

template <std::size_t CallbackSize, typename... Args>
struct binder<CallbackSize, std::tuple<Args...>>
{
    typedef std::tuple<typename convert<CallbackSize, Args>::callback_type...> type;
};
} // namespace detail

template <std::size_t CallbackSize, typename... Events>
class event_loop
{
public:
    template <typename EventType>
    using callback_type = function<void(const EventType&), CallbackSize>;

    template <typename EventType>
    void register_event(const callback_type<EventType>& callback);

    template <typename EventType>
    constexpr void dispatch(const EventType& event);

    template <typename EventType>
    constexpr void unregister();

private:
    typename detail::binder<CallbackSize, std::tuple<Events...>>::type callbacks_;
};

template <std::size_t CallbackSize, typename... Events>
template <typename EventType>
constexpr void event_loop<CallbackSize, Events...>::dispatch(const EventType& event)
{
    if (!std::get<callback_type<EventType>>(callbacks_))
    {
        return;
    }
    std::get<callback_type<EventType>>(callbacks_)(event);
}

template <std::size_t CallbackSize, typename... Events>
template <typename EventType>
constexpr void event_loop<CallbackSize, Events...>::unregister()
{
    std::get<callback_type<EventType>>(callbacks_) = nullptr;
}

template <std::size_t CallbackSize, typename... Events>
template <typename EventType>
void event_loop<CallbackSize, Events...>::register_event(const callback_type<EventType>& callback)
{
    std::get<callback_type<EventType>>(callbacks_) = callback;
}
} // namespace eul
