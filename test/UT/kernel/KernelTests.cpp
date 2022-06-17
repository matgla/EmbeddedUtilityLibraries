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
#include "eul/kernel/service.hpp"


struct EventUpdateServiceC
{
    int a;
};

struct EventUpdateServiceA
{
    int a;
};

struct ServiceB : public eul::kernel::service
{
    ServiceB() : service(this)
    {
    }

    int a{0};
};

struct ServiceC : public eul::kernel::service, // NOLINT(fuchsia-multiple-inheritance)
    public eul::kernel::event_listener<EventUpdateServiceC>
{
    ServiceC() : service(this)
    {
    }

    void handle_event(const EventUpdateServiceC& ev) override
    {
        a = ev.a;
    }

    int a{0};
};

struct ServiceA : public eul::kernel::service,  // NOLINT(fuchsia-multiple-inheritance)
    public eul::kernel::event_listener<EventUpdateServiceA>
{
    explicit ServiceA(eul::kernel::kernel* kernel)
        : service(this)
        , kernel_(*kernel)
    {
    }

    void handle_event(const EventUpdateServiceA& ev) override
    {
        a = ev.a;
        update_service_c(ev.a);
    }

    void update_service_b(int value)
    {
        auto* b = kernel_.get_service<ServiceB>();
        b->a= value;
    }

    void update_service_c(int value) const
    {
        kernel_.post_event(EventUpdateServiceC{value});
    }

    int a{0};
    eul::kernel::kernel& kernel_;
};


TEST_CASE("KernelShould", "[KernelTests]")
{
    SECTION("Register and provide services")
    {
        eul::kernel::kernel kernel;

        ServiceA a(&kernel);
        ServiceB b;

        a.a = 1;
        b.a = 2;

        kernel.register_service(&a);
        kernel.register_service(&b);

        auto* serviceA = kernel.get_service<ServiceA>();
        constexpr int test_value = 14;
        serviceA->update_service_b(test_value);

        REQUIRE(a.a == 1);
        REQUIRE(b.a == test_value);

        serviceA->a = 2;
        REQUIRE(a.a == 2);
        REQUIRE(b.a == test_value);
    }

    SECTION("Handle events")
    {
        eul::kernel::kernel kernel;

        ServiceA a(&kernel);
        ServiceB b;
        ServiceC c;

        a.a = 1;
        b.a = 2;
        c.a = 3;

        kernel.register_service(&a);
        kernel.register_service(&b);
        kernel.register_service(&c);

        constexpr int test_value = 11;
        kernel.post_event(EventUpdateServiceA{test_value});

        REQUIRE(a.a == test_value);
        REQUIRE(b.a == 2);
        REQUIRE(c.a == test_value);
    }
    SECTION("Return nullptr if not registered service")
    {
        eul::kernel::kernel kernel;

        ServiceB* b = kernel.get_service<ServiceB>();
        const ServiceB* c = kernel.get_service<ServiceB>();

        REQUIRE(!b);
        REQUIRE(!c);
        
    }
}
