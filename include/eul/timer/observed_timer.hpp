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

#include "eul/timer/ITimer.hpp"

#include "eul/container/observable/observing_node.hpp"

namespace eul
{
namespace timer
{

class observed_timer : public ITimer
{
public:
    observed_timer()
        : observing_node_(this)
    {
    }

    eul::container::observing_node<observed_timer*>& observing_node()
    {
        return observing_node_;
    }

protected:
    eul::container::observing_node<observed_timer*> observing_node_;
};

} // namespace timer
} // namespace eul
