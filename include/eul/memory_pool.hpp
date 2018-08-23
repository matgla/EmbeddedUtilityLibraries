#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include "eul/assert.hpp"

namespace eul
{

template <std::size_t Size>
class MemoryPool final
{
private:
    struct AllocationInfo
    {
        std::size_t size;
    };

    using AlignedStorageType = typename std::aligned_storage<sizeof(void*), alignof(void*)>::type;

public:
    MemoryPool()
        : firstObjectAddress_(nullptr)
    {
    }

    template <typename T, typename... Args>
    T* allocate(Args... args)
    {
        auto* positionInMemory = getNext();
        // new (positionInMemory) AllocationInfo{sizeof(T)};
        // auto* object = new (positionInMemory + sizeof(AllocationInfo)) T(std::forward<Args>(args)...);

        for (const auto& data : data_)
        {
            std::cerr << std::hex << "0x";
            for (const auto byte : data.__data)
            {
                std::cerr << std::to_string(byte);
            }
            std::cerr << " ";
        }

        std::cerr << std::endl;
        return nullptr;
    }

private:
    AlignedStorageType* getNext()
    {
        if (firstObjectAddress_ == nullptr)
        {
            firstObjectAddress_ = data_.data();
        }
    }

    AlignedStorageType* firstObjectAddress_;
    std::array<AlignedStorageType, Size> data_;
};

} // namespace eul
