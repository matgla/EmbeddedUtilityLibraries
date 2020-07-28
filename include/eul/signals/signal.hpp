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

#include "eul/container/observable/observing_list.hpp"
#include "eul/function.hpp"
#include "eul/signals/slot.hpp"

namespace eul::signals
{

template <class, std::size_t Size = 1>
class signal;

template <std::size_t Size, class ReturnType, class... Args>
class signal<ReturnType(Args...), Size>
{
public:
    signal() = default;
    signal(const signal& other) = delete;
    signal& operator=(const signal& other) = delete;
    signal(signal&& other) noexcept = default;
    signal& operator=(signal&& other) noexcept = default;
    ~signal() = default;

    using slot_t = slot<ReturnType(Args...), Size>;

    void connect(slot_t& slot)
    {
        slots_.push_back(slot.observing_node());
    }

    void emit(Args... args) const
    {
        for (const auto& slot_observer : slots_)
        {
            const auto& slot = *(slot_observer.data());
            if (slot)
            {
                slot(std::forward<Args>(args)...);
            }
        }
    }

    void disconnect_all()
    {
        slots_.clear();
    }

private:
    using observing_list = eul::container::observing_list<typename slot_t::observed_type>;
    observing_list slots_;
};

} // namespace eul::signals

