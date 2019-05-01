#pragma once

#include <chrono>

 #include <eul/time/ITimeProvider.hpp>

namespace stubs
{
namespace time
{

class TimeStub : public eul::time::ITimeProvider
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
