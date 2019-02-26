#include <catch.hpp>

#include "eul/container/iterator/index_iterator.hpp"

struct Data
{
    int value = 0;
};

struct TestingObject
{
    using value_type = Data;
    Data& operator[](std::size_t index)
    {
        this->index = index;
        return value;
    }

    Data value        = {0};
    std::size_t index = 0;
};

TEST_CASE("IndexIterator should", "[IndexIteratorTests]")
{
    using SutType = eul::container::iterator::index_iterator<TestingObject>;

    SECTION("PostIncrement")
    {
        TestingObject stub;
        SutType sut(stub, 0);
        *sut;
        REQUIRE(stub.index == 0);

        auto it = sut++;
        *sut;
        REQUIRE(stub.index == 1);
        *it;
        REQUIRE(stub.index == 0);
    }

    SECTION("PreIncrement")
    {
        TestingObject stub;
        SutType sut(stub, 0);
        *sut;
        REQUIRE(stub.index == 0);

        auto it = ++sut;
        *sut;
        REQUIRE(stub.index == 1);
        *it;
        REQUIRE(stub.index == 1);
    }

    SECTION("Access value")
    {
        TestingObject stub{15, 10};
        SutType sut(stub, 0);
        REQUIRE(stub.index == 10);

        REQUIRE((*sut).value == 15);
        REQUIRE(sut->value == 15);
    }

    SECTION("compare iterators")
    {
        TestingObject stub{15, 10};
        SutType sut(stub, 0);
        SutType sut2(stub, 0);
        SutType sut3(stub, 3);

        REQUIRE(sut == sut2);
        REQUIRE(sut != sut3);
        REQUIRE(sut2 != sut3);
    }
}