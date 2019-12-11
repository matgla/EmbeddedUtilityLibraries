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

#include "eul/timer/timer.hpp"
#include "test/stubs/time/TimeStub.hpp"

namespace eul
{
namespace timer
{

class TimerStub : public timer
{
public:
    using CallbackType = typename timer::CallbackType;
    TimerStub(const CallbackType& callback, const time::i_time_provider& time)
        : timer(callback, time)
    {
    }

    const std::chrono::milliseconds& getStartTime() const
    {
        return this->start_time_;
    }

    const std::chrono::milliseconds& getEndTime() const
    {
        return this->end_time_;
    }

    const time::i_time_provider& getTimeProvider() const
    {
        return this->time_provider_;
    }

    const CallbackType& getCallback() const
    {
        return this->callback_;
    }

    void run() override
    {
        this->fire();
    }
};

TEST_CASE("TimerShould", "[TimerTests]")
{
    SECTION("Initialize timer correctly")
    {
        int counter = 0;
        stubs::time::TimeStub time;

        const TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.getCallback()();
        REQUIRE(counter == 1);

        REQUIRE(timer.getStartTime() == std::chrono::milliseconds(0));
        REQUIRE(timer.getEndTime() == std::chrono::milliseconds(0));
        REQUIRE(&timer.getTimeProvider() == &time);
    }

    SECTION("Set parameters on start")
    {
        int counter = 0;
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.getCallback()();
        REQUIRE(counter == 1);

        REQUIRE(timer.start(std::chrono::milliseconds(5)));
        REQUIRE(timer.getStartTime() == std::chrono::milliseconds(10));
        REQUIRE(timer.getEndTime() == std::chrono::milliseconds(15));
        REQUIRE(&timer.getTimeProvider() == &time);
    }

    SECTION("Set parameters with callback on start")
    {
        int counter = 0;
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.getCallback()();
        REQUIRE(counter == 1);

        int counter2 = 0;
        REQUIRE(timer.start([&counter2]() { counter2 += 10; }, std::chrono::milliseconds(5)));

        timer.getCallback()();
        REQUIRE(counter2 == 10);
        REQUIRE(counter == 1);

        REQUIRE(timer.getStartTime() == std::chrono::milliseconds(10));
        REQUIRE(timer.getEndTime() == std::chrono::milliseconds(15));
        REQUIRE(&timer.getTimeProvider() == &time);
    }

    SECTION("Not set parameters on start when state is running")
    {
        int counter = 0;
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.getCallback()();
        REQUIRE(counter == 1);

        REQUIRE(timer.start(std::chrono::milliseconds(5)));
        ++time;
        REQUIRE(!timer.start(std::chrono::milliseconds(17)));

        REQUIRE(timer.getStartTime() == std::chrono::milliseconds(10));
        REQUIRE(timer.getEndTime() == std::chrono::milliseconds(15));
        REQUIRE(&timer.getTimeProvider() == &time);
    }

    SECTION("Not set parameters with callback on start when state is running")
    {
        int counter = 0;
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.getCallback()();
        REQUIRE(counter == 1);

        int counter2 = 0;
        REQUIRE(timer.start([&counter2]() { counter2 += 10; }, std::chrono::milliseconds(5)));
        ++time;
        REQUIRE(!timer.start(std::chrono::milliseconds(17)));

        timer.getCallback()();
        REQUIRE(counter2 == 10);
        REQUIRE(counter == 1);

        REQUIRE(timer.getStartTime() == std::chrono::milliseconds(10));
        REQUIRE(timer.getEndTime() == std::chrono::milliseconds(15));
        REQUIRE(&timer.getTimeProvider() == &time);
    }

    SECTION("Invoke callback")
    {
        int counter = 0;
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        TimerStub timer([&counter]() { counter++; }, time);

        REQUIRE(counter == 0);
        timer.run();
        REQUIRE(counter == 1);
    }
}


} // namespace timer
} // namespace eul
