#include "catch.hpp"

#include "eul/observer.hpp"
#include "eul/utils.hpp"

TEST_CASE("Observer should", "[Observer]")
{
    SECTION("Forward calls")
    {
        int int_called_with       = 0;
        bool custom_called        = false;
        double double_called_with = 0.0;

        struct Custom
        {
        };

        eul::Observer observer{
            [&int_called_with](const int i) { int_called_with = i; },
            [&double_called_with](const double d) { double_called_with = d; },
            [&custom_called](const Custom& c) { UNUSED(c); custom_called = true; }};

        observer(123);
        observer(Custom{});
        observer(432.123);

        REQUIRE(int_called_with == 123);
        REQUIRE(double_called_with == 432.123);
        REQUIRE(custom_called);
    }
}
