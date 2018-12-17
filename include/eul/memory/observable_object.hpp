#pragma once

#include <utility>

#include "eul/container/observable/observing_list.hpp"
#include "eul/memory/observer_ptr.hpp"

namespace eul
{
namespace memory
{

template <typename T>
class observable_object
{
public:
    template <typename... Args>
    observable_object(Args&&... args);

    observable_object(observable_object&&)      = default;
    observable_object(const observable_object&) = delete;

    observable_object<T>& operator=(const observable_object<T>&) = delete;
    observable_object<T>& operator=(observable_object<T>&&) = default;

    T* operator->();
    const T* operator->() const;

    T& operator*();
    const T& operator*() const;

    void register_observer(observer_ptr<T>& observer);

    bool is_observed_by(const observer_ptr<T>& observer) const;

private:
    T object_;

    container::observing_list<container::observing_node<T*>> observers_;
};

template <typename T>
template <typename... Args>
observable_object<T>::observable_object(Args&&... args) : object_{args...}
{
}

template <typename T>
T* observable_object<T>::operator->()
{
    return &object_;
}

template <typename T>
const T* observable_object<T>::operator->() const
{
    return &object_;
}

template <typename T>
T& observable_object<T>::operator*()
{
    return object_;
}

template <typename T>
const T& observable_object<T>::operator*() const
{
    return object_;
}

template <typename T>
void observable_object<T>::register_observer(observer_ptr<T>& observer)
{
    observer.reset(&object_);

    observers_.push_back(observer.node());
}

template <typename T>
bool observable_object<T>::is_observed_by(const observer_ptr<T>& observer) const
{
    return observers_.find(&observer.node()) != nullptr;
}

} // namespace memory
} // namespace eul