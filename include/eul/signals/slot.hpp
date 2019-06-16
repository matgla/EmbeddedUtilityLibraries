#pragma once

#include <cstddef>

#include "eul/container/observable/observing_node.hpp"
#include "eul/function.hpp"
#include "eul/assert.hpp"

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

    slot()
        : observing_node_(this)
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
        EUL_ASSERT_MSG(callback_, "Slot is not initialized");
        return callback_(std::forward<Args>(args)...);
    }

    ReturnType operator()(Args&&... args)
    {
        EUL_ASSERT_MSG(callback_, "Slot is not initialized");
        return callback_(std::forward<Args>(args)...);
    }

    template <typename CallbackType>
    self_type& operator=(const CallbackType& callback)
    {
        callback_ = callback;
        return *this;
    }

    explicit operator bool() const noexcept
    {
        return callback_.operator bool();
    }
private:
    observed_type observing_node_;
    callback_type callback_;
};

} // namespace signals
} // namespace eul
