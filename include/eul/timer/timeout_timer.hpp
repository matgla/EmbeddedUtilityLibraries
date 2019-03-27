#pragma once

#include "eul/timer/timer.hpp"

namespace eul
{
namespace timer
{

template <typename TimeProviderType>
class TimeoutTimer : public Timer<TimeProviderType>
{
private:
    using TimerBase = Timer<TimeProviderType>;

public:
    TimeoutTimer(const TimeProviderType& timeProvider)
        : TimerBase::Timer(timeProvider)
    {
    }

    void run() override
    {
        if (this->state_ == TimerBase::State::Running)
        {
            if (this->time_provider_.milliseconds() >= this->end_time_)
            {
                this->state_ = TimerBase::State::Idle;
                this->fire();
            }
        }
    }
};

} // namespace timer
} // namespace eul
