// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <chrono>

#include "eul/timer/observed_timer.hpp"
#include "eul/time/i_time_provider.hpp"
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

    timer(const CallbackType& callback, const time::i_time_provider& time_provider)
        : timer(time_provider)
    {
        callback_ = callback;
    }

    timer(const time::i_time_provider& time_provider)
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

    const time::i_time_provider& time_provider_;

    std::chrono::milliseconds start_time_;
    std::chrono::milliseconds end_time_;
    CallbackType callback_;

    State state_;
};

} // namespace timer
} // namespace eul
