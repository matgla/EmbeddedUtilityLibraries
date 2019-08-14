#pragma once

namespace eul
{
namespace kernel
{

template <typename Event>
struct event_listener
{
    using SelfType = event_listener<Event>;
    constexpr event_listener(const event_listener& ev)
    {
        static_cast<void>(ev);
        listener = this;
    }

    constexpr event_listener()
    {
        listener = this;
    }

    ~event_listener()
    {
        listener = nullptr;
    }

    virtual void handle_event(const Event& event) = 0;

    static SelfType* listener;
};

template <typename T>
typename event_listener<T>::SelfType* event_listener<T>::listener = nullptr;

} // namespace kernel
} // namespace eul
