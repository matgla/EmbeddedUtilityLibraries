#pragma once

#include <cstddef>

#include "eul/container/observable/observing_node.hpp"
#include "eul/function.hpp"

namespace eul
{
namespace signals
{

template <class Functor, std::size_t Size>
class slot;

template <std::size_t Size, class ReturnType, class... Args>
class slot<ReturnType(Args...), Size>
{
public:
    using self_type = slot<ReturnType(Args...), Size>;
    using observed_type = eul::container::observing_node<self_type*>;
    using callback_type = eul::function<ReturnType(Args...), Size>;

    slot(const callback_type& callback)
        : observing_node_(this)
        , callback_(callback)
    {
    }

    observed_type& observing_node()
    {
        return observing_node_;
    }

    void disconnect()
    {
        observing_node_.reset();
    }

    ReturnType operator()(Args&&... args) const
    {
        return callback_(std::forward<Args>(args)...);
    }

    ReturnType operator()(Args&&... args)
    {
        return callback_(std::forward<Args>(args)...);
    }
private:
    observed_type observing_node_;
    const callback_type callback_;
};

} // namespace signals
} // namespace eul
