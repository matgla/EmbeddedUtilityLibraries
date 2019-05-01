#pragma once

#include <chrono>

#include "eul/timer/observed_timer.hpp"
#include "eul/time/ITimeProvider.hpp"
#include "eul/function.hpp"

namespace eul
{
namespace timer
{

class timer : public observed_timer
{
public:
    using CallbackType = eul::function<void(), sizeof(std::size_t)>;

    enum class State
    {
        Running,
        Idle
    };

    timer(const CallbackType& callback, const time::ITimeProvider& time_provider)
        : timer(time_provider)
    {
        callback_ = callback;
    }

    timer(const time::ITimeProvider& time_provider)
        : time_provider_(time_provider),
          start_time_(0), end_time_(0), state_(State::Idle)
    {
    }

    bool start(const CallbackType& callback, const std::chrono::milliseconds& time)
    {
        if (start(time))
        {
            callback_ = callback;
            return true;
        }
        return false;
    }

    bool start(const std::chrono::milliseconds& time)
    {
        if (state_ == State::Running)
        {
            return false;
        }

        start_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(time_provider_.milliseconds());
        end_time_   = start_time_ + time;
        state_      = State::Running;

        return true;
    }

    bool stop()
    {
        if (state_ == State::Running)
        {
            state_ = State::Idle;
            return true;
        }
        return false;
    }

    void setCallback(const CallbackType& callback)
    {
        callback_ = callback;
    }

protected:
    void fire()
    {
        if (callback_)
        {
            callback_();
        }
    }

    const time::ITimeProvider& time_provider_;

    std::chrono::milliseconds start_time_;
    std::chrono::milliseconds end_time_;
    CallbackType callback_;

    State state_;
};

} // namespace timer
} // namespace eul
