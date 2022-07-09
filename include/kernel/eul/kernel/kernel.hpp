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
#include <tuple>
#include <type_traits>

#include "eul/utils/assert.hpp"
#include "eul/container/observable/observing_list.hpp"
#include "eul/kernel/event_listener.hpp"
#include "eul/kernel/service.hpp"
#include "eul/kernel/typeid.hpp"

namespace eul::kernel
{

class kernel
{
public:
    void register_service(service* service)
    {
        services_.push_back(service->observing_node());
    }

    template <typename ServiceType>
    [[nodiscard]] const ServiceType* get_service() const
    {
        const auto service_id = type_id<ServiceType>();

        for (const auto & service : services_)
        {
            if (service.data()->get_id() == service_id)
            {
                return service.data()->get<ServiceType>();
            }
        }
        eul_assert_msg(false, "Trying to retrieve unregistered service");
        return nullptr;
    }

    template <typename ServiceType>
    ServiceType* get_service()
    {
        const auto service_id = type_id<ServiceType>();

        for (auto& service : services_)
        {
            if (service.data()->get_id() == service_id)
            {
                return service.data()->get<ServiceType>();
            }
        }
        eul_assert_msg(false, "Trying to retrieve unregistered service");
        return nullptr;
    }

    template <typename EventType>
    constexpr void post_event(const EventType& event) const
    {
        event_listener<EventType>::post_event(event);
    }

private:
    eul::container::observing_list<eul::container::observing_node<service*>> services_;
};

} // namespace eul::kernel
