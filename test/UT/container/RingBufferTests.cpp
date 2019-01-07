#include <catch.hpp>

#include "eul/container/ring_buffer.hpp"


TEST_CASE("Ring buffer should", "[RingBufferTests]")
{
    SECTION("push elements")
    {
        eul::container::ring_buffer<int, 4> sut;

        REQUIRE(sut.size() == 0);
        sut.push(1);
        sut.push(2);
        sut.push(3);
        sut.push(4);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut.pop() == 1);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 2);
        REQUIRE(sut.pop() == 3);
        REQUIRE(sut.pop() == 4);
        REQUIRE(sut.size() == 0);
    }

    SECTION("push override elements")
    {
        eul::container::ring_buffer<int, 3> sut;

        REQUIRE(sut.size() == 0);
        sut.push(1);
        sut.push(2);
        sut.push(3);
        sut.push(4);
        sut.push(5);

        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 3);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.pop() == 4);
        REQUIRE(sut.pop() == 5);
        REQUIRE(sut.size() == 0);

        sut.push(5);
        sut.push(7);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.pop() == 5);
        REQUIRE(sut.size() == 1);

        sut.push(8);
        sut.push(9);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 7);
        REQUIRE(sut.size() == 2);

        sut.push(10);
        sut.push(11);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 9);
        REQUIRE(sut.size() == 2);

        sut.push(12);
        sut.push(13);
        sut.push(14);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop() == 12);
        REQUIRE(sut.size() == 2);
    }

    SECTION("return front element")
    {
        eul::container::ring_buffer<int, 3> sut;

        REQUIRE(sut.size() == 0);
        sut.push(1);
        sut.push(2);
        sut.push(3);
        sut.push(4);
        sut.push(5);

        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front() == 3);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front() == 3);

        REQUIRE(sut.pop() == 3);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front() == 4);
        REQUIRE(sut.size() == 2);
    }
}
