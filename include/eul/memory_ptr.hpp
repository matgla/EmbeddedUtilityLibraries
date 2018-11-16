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

    operator T*() const
    {
        return reinterpret_cast<T*>(address_);
    }

    T* operator->() const
    {
        return operator T*();
    }

private:
    std::intptr_t address_;
};

} // namespace eul
