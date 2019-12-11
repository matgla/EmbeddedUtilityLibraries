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

#include <memory>
#include <string_view>
#include <type_traits>
#include <tuple>

#include "eul/assert.hpp"
#include "eul/kernel/typeid.hpp"
#include "eul/kernel/module.hpp"
#include "eul/kernel/event_listener.hpp"
#include "eul/container/observable/observing_list.hpp"

namespace eul
{
namespace kernel
{

class kernel
{
public:
    void register_module(module& module)
    {
        modules_.push_back(module.observing_node());
    }

    template <typename ModuleType>
    const ModuleType* get_module() const
    {
        const auto module_id = type_id<ModuleType>();

        for (auto& module : modules_)
        {
            if (module.data()->get_id() == module_id)
            {
                return module.data()->get<ModuleType>();
            }
        }
        EUL_ASSERT_MSG(false, "Trying to retrieve unregistered module");
        return nullptr;
    }

    template <typename ModuleType>
    ModuleType* get_module()
    {
        const auto module_id = type_id<ModuleType>();

        for (auto& module : modules_)
        {
            if (module.data()->get_id() == module_id)
            {
                return module.data()->get<ModuleType>();
            }
        }
        EUL_ASSERT_MSG(false, "Trying to retrieve unregistered module");
        return nullptr;
    }

    template <typename EventType>
    constexpr void post_event(const EventType& event) const
    {
        if (event_listener<EventType>::listener)
        {
            event_listener<EventType>::listener->handle_event(event);
        }
    }

private:
    eul::container::observing_list<eul::container::observing_node<module*>> modules_;
};


} // namespace kernel
} // namespace eul
