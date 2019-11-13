#pragma once

#include <cstdint>

namespace eul
{

template <typename T>
class memory_ptr
{
public:
    constexpr memory_ptr(std::intptr_t address)
        : address_(address)
    {
    }

    operator volatile T*() const
    {
        return reinterpret_cast<T*>(address_);
    }

    volatile T* operator->() const
    {
        return reinterpret_cast<T*>(address_);
    }

private:
    std::intptr_t address_;
};

} // namespace eul
