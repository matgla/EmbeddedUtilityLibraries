#pragma once

namespace eul
{
namespace timer
{

class ITimer
{
public:
    virtual ~ITimer() = default;

    virtual void run() = 0;
};

} // namespace timer
} // namespace eul
