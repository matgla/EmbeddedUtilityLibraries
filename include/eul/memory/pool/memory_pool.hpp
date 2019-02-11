#include <cstddef>
#include <array>
#include <type_traits>

#include <sstream>
#include <iostream>
#include <string>

#include "eul/memory/pool/unique_ptr.hpp"
#include "eul/memory/pool/details/allocation_header.hpp"

namespace eul
{
namespace memory
{
namespace pool
{

template <typename Type = std::max_align_t, typename SizeType = std::size_t, SizeType Size = 128>
struct memory_pool
{
    using storage_type  = typename std::aligned_storage<sizeof(uint8_t), alignof(Type)>::type;
    using size_type = std::size_t;
    constexpr static uint8_t alignment = alignof(Type);

    memory_pool()
        : start_(0), current_(0), end_(0)
    {
    }

    template <typename T>
    constexpr static T align(T a)
    {
        return a + (alignment - a%alignment);
    }

    template <typename T, typename... Args>
    auto allocate(Args&&... args)
    {
        static_assert(alignof(T) <= alignof(Type), "Can't allocate object with higher alignment than memory pool has!");
        constexpr auto header_size = align(sizeof(details::allocation_header<SizeType>));

        constexpr auto allocation_size = align(sizeof(T));

        new (&data_[current_]) details::allocation_header<SizeType>(details::allocation_header<SizeType>::State::Reserved, allocation_size);
        const auto header_position_in_buffer = current_;

        current_ += header_size;
        auto* object = new (&data_[current_]) T{std::forward<Args>(args)...};
        current_ += allocation_size;

        // current_                                   = end_;

        // std::cout << "Allocation of header: " << (int)(allocationSize) << ", at: " << std::hex << current_ << std::endl;
        // details::allocation_header<SizeType>* allocationHeader = new (&data_[current_]) details::allocation_header<SizeType>(details::allocation_header<SizeType>::State::Reserved, allocationSize);
        // SizeType headerPositionInBuffer            = current_;
        // end_         = current_ + allocationSize;
        // std::cout << "Position of object: " << headerPositionInBuffer + allocationHeader->size() << std::endl;
        // auto* object = new (&data_[headerPositionInBuffer + allocationHeader->size()]) T{std::forward<Args>(args)...};

        const auto deallocation_callback = [this](auto* pool_ptr)
        {
            if (pool_ptr)
            {
                this->deallocate(*pool_ptr);
            }
        };

        return make_unique_ptr(object, deallocation_callback, header_position_in_buffer);
    }

    void deallocate(const auto& data)
    {
        details::allocation_header<SizeType>* header =
            reinterpret_cast<details::allocation_header<SizeType>*>(&data_[data.position()]);
    }

    int start_;
    int current_;
    int end_;
    std::array<uint8_t, Size> data_;
};

}
}
} // namespace eul
