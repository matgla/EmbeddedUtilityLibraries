#pragma once

#include "eul/container/observable/observing_node.hpp"

#include <iostream>

namespace eul
{
namespace memory
{

template <typename T>
class observer_ptr
{
public:
    observer_ptr() : node_{nullptr}
    {
    }

    ~observer_ptr()
    {
        std::cerr << "~observer_ptr()" << std::endl;
    }

    bool is_valid() const
    {
        return node_.data() != nullptr && node_.is_subscribed() != false;
    }

    void reset(T* newObject)
    {
        std::cerr << "reset node with new value" << std::endl;
        node_.reset(newObject);
    }

    container::observing_node<T*>& node()
    {
        return node_;
    }

    container::observing_node<T*> node_;
};

} // namespace memory
} // namespace eul
