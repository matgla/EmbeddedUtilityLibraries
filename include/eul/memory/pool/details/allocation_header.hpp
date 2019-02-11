#pragma once

#include <cstdint>

namespace eul
{
namespace memory
{
namespace pool
{
namespace details
{

template <typename SizeType>
class allocation_header
{
public:
    enum class State : uint8_t
    {
        Reserved = 0xAC,
        Free     = 0x00
    };

    allocation_header(const State state, const SizeType size);
    const auto state() const;
    const SizeType size() const;

private:
    const State state_;
    uint8_t size_[sizeof(SizeType)];
};

// implementation

template <typename SizeType>
allocation_header<SizeType>::allocation_header(const State state, const SizeType size)
    : state_(state)
{
    const uint8_t* sizePtr = reinterpret_cast<const uint8_t*>(&size);
    for (auto& byte : size_)
    {
        byte = *sizePtr;
        ++sizePtr;
    }
}
template <typename SizeType>
const auto allocation_header<SizeType>::state() const
{
    return state_;
}

template <typename SizeType>
const SizeType allocation_header<SizeType>::size() const
{
    SizeType size;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&size);
    for (std::size_t i = 0; i < sizeof(SizeType); i++)
    {
        ptr[i] = size_[i];
    }
    return size;
}

} // namespace details
} // namespace pool
} // namespace memory
} // namespace eul
