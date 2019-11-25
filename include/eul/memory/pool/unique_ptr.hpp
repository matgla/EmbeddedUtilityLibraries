#pragma once

#include <cstddef>
#include <type_traits>

namespace eul
{
namespace memory
{
namespace pool
{

template <typename Type, typename OnDestroyCallbackType>
struct unique_ptr
{
    unique_ptr(const OnDestroyCallbackType& on_destroy) 
        : ptr_(nullptr)
        , on_destroy_(on_destroy)
        , position_in_buffer_(0)
    {
    }
   
    unique_ptr(Type* ptr, const OnDestroyCallbackType& on_destroy, const std::size_t position_in_buffer)
        : ptr_(ptr), on_destroy_(on_destroy), position_in_buffer_(position_in_buffer)
    {
    }

    ~unique_ptr()
    {
        reset();
    }

    Type* operator->() const noexcept
    {
        return ptr_;
    }

    typename std::add_lvalue_reference<Type>::type operator*() const
    {
        return *ptr_;
    }

    bool operator==(std::nullptr_t) const
    {
        return ptr_ == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return ptr_ != nullptr;
    }

    void reset()
    {
        if (!ptr_)
        {
            return;
        }

        ptr_->~Type();
        on_destroy_(this);

        ptr_ = nullptr;
    }

    std::size_t position() const
    {
        return position_in_buffer_;
    }

    Type* ptr_;
    OnDestroyCallbackType on_destroy_;
    std::size_t position_in_buffer_;
};

template <typename Type, typename OnDestroyCallbackType>
constexpr auto make_unique_ptr(Type* ptr,
    const OnDestroyCallbackType& on_destory,
    const std::size_t position_in_buffer)
{
    return unique_ptr(ptr, on_destory, position_in_buffer);
}

template <typename Type, typename OnDestroyCallbackType>
constexpr auto make_unique_ptr(std::nullptr_t, const OnDestroyCallbackType& on_destroy)
{
    return unique_ptr<Type, OnDestroyCallbackType>(on_destroy);
}

} // namespace pool
} // namespace memory
} // namespace eul
