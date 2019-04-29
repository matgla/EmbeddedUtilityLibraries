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

struct ModuleB : public eul::kernel::Module
{
    ModuleB() : Module(this)
    {
    }

    int a;
};

struct ModuleC : public eul::kernel::Module,
    public eul::kernel::EventListener<EventUpdateModuleC>
{
    ModuleC() : Module(this)
    {
    }

    void handle_event(const EventUpdateModuleC& ev) override
    {
        a = ev.a;
    }

    int a;
};

struct ModuleA : public eul::kernel::Module,
    public eul::kernel::EventListener<EventUpdateModuleA>
{
    ModuleA(eul::kernel::Kernel& kernel)
        : Module(this)
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
    eul::kernel::Kernel& kernel_;
};


TEST_CASE("KernelShould", "[KernelTests]")
{
    SECTION("Register and provide modules")
    {
        eul::kernel::Kernel kernel;

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
        eul::kernel::Kernel kernel;

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
