#pragma once

#include <chrono>

 #include <eul/timer/ITimeProvider.hpp>

namespace stubs
{
namespace time
{

class TimeStub : public eul::timer::ITimeProvider
{
public:
    void setTime(const std::chrono::milliseconds& time)
    {
        time_ = time;
    }

    void operator++()
    {
        ++time_;
    }

    void operator--()
    {
        --time_;
    }

    std::chrono::milliseconds milliseconds() const
    {
        return time_;
    }

private:
    std::chrono::milliseconds time_;
};

} // namespace time
} // namespace stubs
