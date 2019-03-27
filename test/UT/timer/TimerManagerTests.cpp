#include <chrono>

#include <catch.hpp>

#include "eul/timer/timeout_timer.hpp"
#include "eul/timer/timer_manager.hpp"

#include "test/stubs/time/TimeStub.hpp"

namespace eul
{
namespace timer
{

TEST_CASE("TimerManagerShould", "[TimerManagerTests]")
{
    SECTION("Register timers")
    {
        stubs::time::TimeStub time;
        time.setTime(std::chrono::seconds(0));

        int counter = 0;
        bool called = false;
        TimerManager sut;
        TimeoutTimer timer(time);
        TimeoutTimer timer2(time);

        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10));

        timer2.start(
            [&called] { called = true; },
            std::chrono::seconds(2));

        sut.register_timer(timer);
        sut.register_timer(timer2);

        REQUIRE(counter == 0);
        sut.run();
        REQUIRE(counter == 0);
        time.setTime(std::chrono::seconds(1));
        sut.run();
        REQUIRE(counter == 1);
        REQUIRE(!called);
        time.setTime(std::chrono::seconds(3));

        sut.run();
        REQUIRE(counter == 1);
        REQUIRE(called);
    }

    SECTION("Automatically deregister dead timers")
    {
        stubs::time::TimeStub time;
        time.setTime(std::chrono::seconds(0));

        int counter = 0;
        bool called = false;
        TimerManager sut;
        TimeoutTimer timer(time);


        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10));

        sut.register_timer(timer);

        {
            TimeoutTimer timer2(time);
            timer2.start(
                [&called] { called = true; },
                std::chrono::seconds(2));

            sut.register_timer(timer2);
        }
        time.setTime(std::chrono::seconds(3));

        sut.run();
        REQUIRE(counter == 1);
        REQUIRE(called == false);
    }

    SECTION("Deregister timer")
    {
        stubs::time::TimeStub time;
        time.setTime(std::chrono::seconds(0));

        int counter = 0;
        bool called = false;
        TimerManager sut;
        TimeoutTimer timer(time);


        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10));

        sut.register_timer(timer);

        TimeoutTimer timer2(time);
        timer2.start(
            [&called] { called = true; },
            std::chrono::seconds(2));

        sut.register_timer(timer2);

        time.setTime(std::chrono::seconds(3));

        sut.deregister_timer(timer);
        sut.run();
        REQUIRE(counter == 0);
        REQUIRE(called);
    }
}

} // namespace timer
} // namespace eul
