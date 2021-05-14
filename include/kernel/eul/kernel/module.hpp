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

class module
{
public:
    using ModuleNode = eul::container::observing_node<module*>;

    template <typename ModuleType>
    module(typeid_t id, ModuleType& module)
        : observing_node_(this)
        , id_(id)
        , module_(&module)
    {
    }

    template <typename ModuleType>
    explicit module(ModuleType* module)
        : observing_node_(this)
        , id_(type_id<ModuleType>())
        , module_(module)
    {
    }

    virtual ~module() = default;

    template <typename ModuleType>
    auto* get()
    {
        return static_cast<ModuleType*>(module_);
    }

    template <typename ModuleType>
    [[nodiscard]] const auto* get() const
    {
        return static_cast<const ModuleType*>(module_);
    }

    ModuleNode& observing_node()
    {
        return observing_node_;
    }


    [[nodiscard]] typeid_t get_id() const
    {
        return id_;
    }
private:
    ModuleNode observing_node_;
    typeid_t id_;
    void* module_;
};

} // namespace eul::kernel
