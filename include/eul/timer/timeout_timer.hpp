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

#include "eul/time/i_time_provider.hpp"
#include "eul/timer/timer.hpp"

namespace eul::timer
{

class timeout_timer : public timer
{
public:
    explicit timeout_timer(const time::i_time_provider& timeProvider)
        : timer(timeProvider)
    {
    }

    void run() override
    {
        if (get_state() == State::Running)
        {
            if (get_time_provider().milliseconds() >= get_endtime()) // NOLINT(modernize-use-nullptr)
            {
                set_state(State::Idle);
                fire();
            }
        }
    }
};

} // namespace eul::timer
