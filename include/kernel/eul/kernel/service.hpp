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

#include "eul/container/observable/observing_node.hpp"
#include "eul/kernel/typeid.hpp"

namespace eul::kernel
{

class service
{
public:
    using ServiceNode = eul::container::observing_node<service*>;

    template <typename ServiceType>
    service(typeid_t id, ServiceType& service)
        : observing_node_(this)
        , id_(id)
        , service_(&service)
    {
    }

    template <typename ServiceType>
    explicit service(ServiceType* service)
        : observing_node_(this)
        , id_(type_id<ServiceType>())
        , service_(service)
    {
    }

    virtual ~service() = default;

    template <typename ServiceType>
    auto* get()
    {
        return static_cast<ServiceType*>(service_);
    }

    template <typename ServiceType>
    [[nodiscard]] const auto* get() const
    {
        return static_cast<const ServiceType*>(service_);
    }

    ServiceNode& observing_node()
    {
        return observing_node_;
    }


    [[nodiscard]] typeid_t get_id() const
    {
        return id_;
    }
private:
    ServiceNode observing_node_;
    typeid_t id_;
    void* service_;
};

} // namespace eul::kernel
