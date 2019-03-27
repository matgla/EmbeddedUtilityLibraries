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

        TimeoutTimer timer(time);

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
