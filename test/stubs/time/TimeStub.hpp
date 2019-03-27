#pragma once

#include <chrono>

namespace stubs
{
namespace time
{

class TimeStub
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

    const std::chrono::milliseconds& milliseconds() const
    {
        return time_;
    }

private:
    std::chrono::milliseconds time_;
};

} // namespace time
} // namespace stubs
