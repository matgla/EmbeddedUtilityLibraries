#pragma once

#include <chrono>

namespace eul
{
namespace time
{

class ITimeProvider
{
public:
    virtual ~ITimeProvider() = default;

    virtual std::chrono::milliseconds milliseconds() const = 0;
};

} // namespace time
} // namespace eul
