#pragma once

#include "eul/timer/timer.hpp"
#include "eul/time/ITimeProvider.hpp"

namespace eul
{
namespace timer
{

class timeout_timer : public timer
{
public:
    timeout_timer(const time::ITimeProvider& timeProvider)
        : timer(timeProvider)
    {
    }

    void run() override
    {
        if (state_ == State::Running)
        {
            if (time_provider_.milliseconds() >= end_time_)
            {
                state_ = State::Idle;
                fire();
            }
        }
    }
};

} // namespace timer
} // namespace eul
