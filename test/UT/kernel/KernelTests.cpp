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

#include <catch.hpp>

#include "eul/kernel/kernel.hpp"
#include "eul/kernel/module.hpp"


struct EventUpdateModuleC
{
    int a;
};

struct EventUpdateModuleA
{
    int a;
};

struct ModuleB : public eul::kernel::module
{
    ModuleB() : module(this)
    {
    }

    int a;
};

struct ModuleC : public eul::kernel::module,
    public eul::kernel::event_listener<EventUpdateModuleC>
{
    ModuleC() : module(this)
    {
    }

    void handle_event(const EventUpdateModuleC& ev) override
    {
        a = ev.a;
    }

    int a;
};

struct ModuleA : public eul::kernel::module,
    public eul::kernel::event_listener<EventUpdateModuleA>
{
    ModuleA(eul::kernel::kernel& kernel)
        : module(this)
        , kernel_(kernel)
    {
    }

    void handle_event(const EventUpdateModuleA& ev) override
    {
        a = ev.a;
        update_module_c(ev.a);
    }

    void update_module_b(int value)
    {
        auto* b = kernel_.get_module<ModuleB>();
        b->a= value;
    }

    void update_module_c(int value)
    {
        kernel_.post_event(EventUpdateModuleC{value});
    }

    int a;
    eul::kernel::kernel& kernel_;
};


TEST_CASE("KernelShould", "[KernelTests]")
{
    SECTION("Register and provide modules")
    {
        eul::kernel::kernel kernel;

        ModuleA a(kernel);
        ModuleB b;

        a.a = 1;
        b.a = 2;

        kernel.register_module(a);
        kernel.register_module(b);

        auto* moduleA = kernel.get_module<ModuleA>();
        moduleA->update_module_b(14);

        REQUIRE(a.a == 1);
        REQUIRE(b.a == 14);

        moduleA->a = 2;
        REQUIRE(a.a == 2);
        REQUIRE(b.a == 14);
    }

    SECTION("Handle events")
    {
        eul::kernel::kernel kernel;

        ModuleA a(kernel);
        ModuleB b;
        ModuleC c;

        a.a = 1;
        b.a = 2;
        c.a = 3;

        kernel.register_module(a);
        kernel.register_module(b);
        kernel.register_module(c);

        kernel.post_event(EventUpdateModuleA{11});

        REQUIRE(a.a == 11);
        REQUIRE(b.a == 2);
        REQUIRE(c.a == 11);
    }
}
