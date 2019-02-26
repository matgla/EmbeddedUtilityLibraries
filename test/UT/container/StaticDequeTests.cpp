#include "catch.hpp"

#include "eul/container/static_deque.hpp"

TEST_CASE("StaticDeque should", "[StaticDeque]")
{
    SECTION("not push_back elements when overflowed")
    {
        eul::container::static_deque<int, 1> sut;

        REQUIRE(sut.size() == 0);
        REQUIRE(sut.push_back(1) == true);
        REQUIRE(sut.push_back(2) == false);
        REQUIRE(sut.size() == 1);
    }

    SECTION("not push_front elements when overflowed")
    {
        eul::container::static_deque<int, 1> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_front(2) == false);
        REQUIRE(sut.size() == 1);
    }

    SECTION("push_back elements")
    {
        eul::container::static_deque<int, 3> sut;

        REQUIRE(sut.push_back(1) == true);
        REQUIRE(sut.push_back(2) == true);
        REQUIRE(sut.push_back(3) == true);

        REQUIRE(sut[0] == 1);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 3);
        REQUIRE(sut.size() == 3);
    }

    SECTION("push_front elements")
    {
        eul::container::static_deque<int, 4> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_front(2) == true);
        REQUIRE(sut.push_front(3) == true);

        REQUIRE(sut[0] == 3);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 1);
        REQUIRE(sut.size() == 3);
    }

    SECTION("mixed push_back and front elements")
    {
        eul::container::static_deque<int, 4> sut;

        REQUIRE(sut.push_front(1) == true);
        REQUIRE(sut.push_back(2) == true);
        REQUIRE(sut.push_front(3) == true);
        REQUIRE(sut.push_back(4) == true);

        REQUIRE(sut[0] == 3);
        REQUIRE(sut[1] == 1);
        REQUIRE(sut[2] == 2);
        REQUIRE(sut[3] == 4);
        REQUIRE(sut.size() == 4);
    }
}