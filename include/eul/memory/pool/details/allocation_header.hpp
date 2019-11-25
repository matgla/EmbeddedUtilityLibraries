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

class allocation_header
{
public:
    enum class State : uint8_t
    {
        Reserved = 0xAC,
        Free     = 0x00
    };

    allocation_header(const State state, const std::size_t size);
    State state() const;
    std::size_t size() const;

private:
    const State state_;
    const std::size_t size_;
};

// implementation

allocation_header::allocation_header(const State state, const std::size_t size)
    : state_(state)
    , size_(size)
{
}

allocation_header::State allocation_header::state() const
{
    return state_;
}

std::size_t allocation_header::size() const
{
    return size_;
}

} // namespace details
} // namespace pool
} // namespace memory
} // namespace eul
