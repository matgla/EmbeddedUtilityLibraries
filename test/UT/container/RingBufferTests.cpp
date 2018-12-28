#include <catch.hpp>

#include "eul/container/ring_buffer.hpp"


TEST_CASE("Ring buffer should", "[RingBufferTests]")
{
    SECTION("push_back elements")
    {
        eul::container::ring_buffer<int, 4> sut;

        REQUIRE(sut.size() == 0);
        sut.push_back(1);
        sut.push_back(2);
        sut.push_back(3);
        sut.push_back(4);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut.pop_back() == 4);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop_back() == 3);
        REQUIRE(sut.pop_back() == 2);
        REQUIRE(sut.pop_back() == 1);
        REQUIRE(sut.size() == 0);
    }

    SECTION("push_back elements")
    {
        eul::container::ring_buffer<int, 4> sut;

        REQUIRE(sut.size() == 0);
        sut.push_back(1);
        sut.push_back(2);
        sut.push_back(3);
        sut.push_back(4);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut.pop_back() == 4);
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.pop_back() == 3);
        REQUIRE(sut.pop_back() == 2);
        REQUIRE(sut.pop_back() == 1);
        REQUIRE(sut.size() == 0);
    }
}
