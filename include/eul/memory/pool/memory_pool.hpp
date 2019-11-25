#include <cstddef>
#include <array>
#include <type_traits>

#include <string>

#include <iostream>

#include "eul/memory/pool/unique_ptr.hpp"
#include "eul/memory/pool/details/allocation_header.hpp"

namespace eul
{
namespace memory
{
namespace pool
{

template <std::size_t Size = 128, typename AlignmentType = std::max_align_t>
struct memory_pool
{
public:
    constexpr static uint8_t alignment = alignof(AlignmentType);
    using storage_type = typename std::aligned_storage<sizeof(uint8_t), alignment>::type;
    using self_type = memory_pool<Size, AlignmentType>;

    memory_pool()
        : start_(0), current_(0), end_(0)
    {
    }

    template <typename T, typename... Args>
    auto allocate(Args&&... args)
    {
        static_assert(alignof(T) <= alignment, "Can't allocate object with higher alignment than memory pool has!");
        constexpr std::size_t header_size = align(sizeof(details::allocation_header));
        constexpr std::size_t allocation_size = align(sizeof(T));
        
        const auto deallocation_callback = [this](const auto* pool_ptr)
        {
            if (pool_ptr)
            {
                this->deallocate(*pool_ptr);
            }
        };

        std::cerr << "Header size: " << header_size << ", allocation_size: " << allocation_size << ", Size: " << Size << ", current_: " << current_ << std::endl;
        if (header_size + allocation_size >= Size - current_)
        {
            return make_unique_ptr<T>(nullptr, deallocation_callback);
        }

        new (&data_[current_]) details::allocation_header(details::allocation_header::State::Reserved, allocation_size);
        const auto header_position_in_buffer = current_;

        current_ += header_size;
        T* object = new (&data_[current_]) T{std::forward<Args>(args)...};
        current_ += allocation_size;

        return make_unique_ptr(object, deallocation_callback, header_position_in_buffer);
    }

    void deallocate(const auto& data)
    {
        (void)(data);
       // details::allocation_header<SizeType>* header =
      //      reinterpret_cast<details::allocation_header<SizeType>*>(&data_[data.position()]);
    }
private:
    template <typename T>
    constexpr static T align(T a)
    {
        return a % alignment ? a + (alignment - a % alignment) : a;
    }

    std::size_t start_;
    std::size_t current_;
    std::size_t end_;
    storage_type data_[Size];
};

}
}
} // namespace eul
