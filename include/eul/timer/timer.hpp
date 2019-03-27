#pragma once

#include <chrono>

#include "eul/timer/observed_timer.hpp"

#include "eul/function.hpp"

namespace eul
{
namespace timer
{

template <typename TimeProviderType>
class Timer : public ObservedTimer
{
public:
    using CallbackType = eul::function<void(), sizeof(std::size_t)>;

    enum class State
    {
        Running,
        Idle
    };

    Timer(const CallbackType& callback, const TimeProviderType& time_provider)
        : Timer(time_provider)
    {
        callback_ = callback;
    }

    Timer(const TimeProviderType& time_provider)
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

    const TimeProviderType& time_provider_;

    std::chrono::milliseconds start_time_;
    std::chrono::milliseconds end_time_;
    CallbackType callback_;

    State state_;
};

} // namespace timer
} // namespace eul
