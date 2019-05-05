#pragma once

#include "eul/timer/timer.hpp"
#include "eul/time/i_time_provider.hpp"

namespace eul
{
namespace timer
{

class timeout_timer : public timer
{
public:
    timeout_timer(const time::i_time_provider& timeProvider)
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
