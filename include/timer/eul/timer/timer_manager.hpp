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

#include "eul/timer/observed_timer.hpp"

#include "eul/container/observable/observing_list.hpp"

namespace eul::timer
{

class timer_manager
{
public:
    timer_manager() = default;

    void register_timer(observed_timer* timer)
    {
        timers_.push_back(timer->observing_node());
    }

    static void deregister_timer(observed_timer* timer)
    {
        timer->observing_node().reset();
    }

    void run()
    {
        for (auto& timer : timers_)
        {
            timer.data()->run();
        }
    }

private:
    eul::container::observing_list<eul::container::observing_node<observed_timer*>> timers_;
};

} // namespace eul::timer
