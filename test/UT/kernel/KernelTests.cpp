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

#include <catch2/catch_test_macros.hpp>

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

    int a{0};
};

struct ModuleC : public eul::kernel::module, // NOLINT(fuchsia-multiple-inheritance)
    public eul::kernel::event_listener<EventUpdateModuleC>
{
    ModuleC() : module(this)
    {
    }

    void handle_event(const EventUpdateModuleC& ev) override
    {
        a = ev.a;
    }

    int a{0};
};

struct ModuleA : public eul::kernel::module,  // NOLINT(fuchsia-multiple-inheritance)
    public eul::kernel::event_listener<EventUpdateModuleA>
{
    explicit ModuleA(eul::kernel::kernel* kernel)
        : module(this)
        , kernel_(*kernel)
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

    void update_module_c(int value) const
    {
        kernel_.post_event(EventUpdateModuleC{value});
    }

    int a{0};
    eul::kernel::kernel& kernel_;
};


TEST_CASE("KernelShould", "[KernelTests]")
{
    SECTION("Register and provide modules")
    {
        eul::kernel::kernel kernel;

        ModuleA a(&kernel);
        ModuleB b;

        a.a = 1;
        b.a = 2;

        kernel.register_module(&a);
        kernel.register_module(&b);

        auto* moduleA = kernel.get_module<ModuleA>();
        constexpr int test_value = 14;
        moduleA->update_module_b(test_value);

        REQUIRE(a.a == 1);
        REQUIRE(b.a == test_value);

        moduleA->a = 2;
        REQUIRE(a.a == 2);
        REQUIRE(b.a == test_value);
    }

    SECTION("Handle events")
    {
        eul::kernel::kernel kernel;

        ModuleA a(&kernel);
        ModuleB b;
        ModuleC c;

        a.a = 1;
        b.a = 2;
        c.a = 3;

        kernel.register_module(&a);
        kernel.register_module(&b);
        kernel.register_module(&c);

        constexpr int test_value = 11;
        kernel.post_event(EventUpdateModuleA{test_value});

        REQUIRE(a.a == test_value);
        REQUIRE(b.a == 2);
        REQUIRE(c.a == test_value);
    }
}
