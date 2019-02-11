#pragma once

#include <cstddef>
#include <type_traits>

namespace eul
{
namespace memory
{
namespace pool
{

template <typename Type, typename OnDestroyCallbackType, typename SizeType>
struct unique_ptr
{
    using size_type = SizeType;

    unique_ptr(Type* ptr, const OnDestroyCallbackType& onDestory, SizeType positionInBuffer)
        : ptr_(ptr), onDestory_(onDestory), positionInBuffer_(positionInBuffer)
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
        onDestory_(this);

        ptr_ = nullptr;
    }

    const size_type position() const
    {
        return positionInBuffer_;
    }

    Type* ptr_;
    OnDestroyCallbackType onDestory_;
    size_type positionInBuffer_;
};

template <typename Type, typename OnDestroyCallbackType, typename SizeType>
constexpr auto make_unique_ptr(Type* ptr,
    const OnDestroyCallbackType& onDestroy, SizeType positionInBuffer)
{
    return unique_ptr(ptr, onDestroy, positionInBuffer);
}

} // namespace pool
} // namespace memory
} // namespace eul
