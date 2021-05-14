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

#include <eul/utils/unused.hpp>

namespace eul::kernel
{

template <typename Event>
struct event_listener
{
    using SelfType = event_listener<Event>;
    constexpr event_listener(const event_listener& ev)
    {
        if (this != &ev)
        {
            listener = this;
        }
    }

    constexpr event_listener()
    {
        listener = this;
    }

    event_listener& operator=(const event_listener& ev)
    {
        if (this != &ev)
        {
            listener = this;
        }
    }

    constexpr event_listener(event_listener&& ev) = delete;
    event_listener& operator=(event_listener&& ev) = delete;
    ~event_listener()
    {
        listener = nullptr;
    }

    virtual void handle_event(const Event& event) = 0;

    static SelfType* listener;
};

template <typename T>
typename event_listener<T>::SelfType* event_listener<T>::listener = nullptr;

} // namespace eul::kernel
