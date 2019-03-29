#pragma once

#include <chrono>

namespace eul
{
namespace timer
{

class ITimeProvider
{
public:
    virtual ~ITimeProvider() = default;

    virtual std::chrono::milliseconds milliseconds() const = 0;
};

} // namespace timer
} // namespace eul
