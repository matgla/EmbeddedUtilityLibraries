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

#include <chrono>

#include <catch.hpp>

#include "eul/timer/timeout_timer.hpp"
#include "eul/timer/timer_manager.hpp"

#include "test/stubs/time/TimeStub.hpp"

namespace eul::timer
{

TEST_CASE("TimerManagerShould", "[TimerManagerTests]")
{
    SECTION("Register timers")
    {
        stubs::time::TimeStub time;
        time.setTime(std::chrono::seconds(0));

        int counter = 0;
        bool called = false;
        timer_manager sut;
        timeout_timer timer(time);
        timeout_timer timer2(time);

        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

        timer2.start(
            [&called] { called = true; },
            std::chrono::seconds(2));

        sut.register_timer(&timer);
        sut.register_timer(&timer2);

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
        timer_manager sut;
        timeout_timer timer(time);


        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

        sut.register_timer(&timer);

        {
            timeout_timer timer2(time);
            timer2.start(
                [&called] { called = true; },
                std::chrono::seconds(2));

            sut.register_timer(&timer2);
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
        timer_manager sut;
        timeout_timer timer(time);


        timer.start(
            [&counter]() {
                counter++;
            },
            std::chrono::milliseconds(10)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

        sut.register_timer(&timer);

        timeout_timer timer2(time);
        timer2.start(
            [&called] { called = true; },
            std::chrono::seconds(2));

        sut.register_timer(&timer2);

        time.setTime(std::chrono::seconds(3));

        timer_manager::deregister_timer(&timer);
        sut.run();
        REQUIRE(counter == 0);
        REQUIRE(called);
    }
}

} // namespace eul::timer
