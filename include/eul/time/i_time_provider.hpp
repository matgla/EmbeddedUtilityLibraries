#pragma once

#include <chrono>

namespace eul
{
namespace time
{

class i_time_provider
{
public:
    virtual ~i_time_provider() = default;

    virtual std::chrono::milliseconds milliseconds() const = 0;
};

} // namespace time
} // namespace eul
