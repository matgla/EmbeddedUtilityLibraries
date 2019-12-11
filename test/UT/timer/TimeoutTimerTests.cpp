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

#include "eul/timer/timeout_timer.hpp"
#include "test/stubs/time/TimeStub.hpp"

namespace eul
{
namespace timer
{

TEST_CASE("TimeoutTimerShould", "[TimeoutTimerTests]")
{
    SECTION("Fire after timeout")
    {
        stubs::time::TimeStub time;
        time.setTime(std::chrono::milliseconds(10));

        timeout_timer timer(time);

        int counter = 0;
        REQUIRE(timer.start([&counter] { counter += 15; }, std::chrono::milliseconds(161)));

        REQUIRE(counter == 0);
        time.setTime(std::chrono::milliseconds(170));
        timer.run();
        REQUIRE(counter == 0);

        time.setTime(std::chrono::milliseconds(171));
        timer.run();
        REQUIRE(counter == 15);

        time.setTime(std::chrono::milliseconds(3 * 161));
        timer.run();
        REQUIRE(counter == 15);

        REQUIRE(timer.start(std::chrono::milliseconds(10)));
        REQUIRE(!timer.start(std::chrono::milliseconds(10)));
        time.setTime(std::chrono::milliseconds(4 * 161));
        timer.run();
        REQUIRE(counter == 30);
    }
}

} // namespace timer
} // namespace eul
