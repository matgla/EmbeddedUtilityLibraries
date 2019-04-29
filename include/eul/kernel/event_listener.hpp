#pragma once

namespace eul
{
namespace kernel
{

template <typename Event>
struct EventListener
{
    using SelfType = EventListener<Event>;
    constexpr EventListener(const EventListener& ev)
    {
        listener = this;
    }

    constexpr EventListener()
    {
        listener = this;
    }

    ~EventListener()
    {
        listener = nullptr;
    }

    virtual void handle_event(const Event& event) = 0;

    static SelfType* listener;
};

template <typename T>
typename EventListener<T>::SelfType* EventListener<T>::listener = nullptr;

} // namespace kernel
} // namespace eul
