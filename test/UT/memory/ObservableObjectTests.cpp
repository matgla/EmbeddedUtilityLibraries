#include <string>

#include "catch.hpp"

#include "eul/memory/observable_object.hpp"

namespace eul
{
namespace memory
{

struct TestingData
{
    std::string name;
    int id;
};

TEST_CASE("Observable object should", "[Memory]")
{
    SECTION("Provide access real object")
    {
        observable_object<TestingData> sut{"name", 2};

        REQUIRE(sut->name == "name");
        REQUIRE((*sut).name == "name");

        REQUIRE(sut->id == 2);
        REQUIRE((*sut).id == 2);

        sut->name = "eh";
        REQUIRE(sut->name == "eh");
    }

    SECTION("Register observer")
    {
        observer_ptr<TestingData> ptr;
        REQUIRE(ptr.is_valid() == false);
        {
            observable_object<TestingData> sut{"name", 2};
            sut.register_observer(ptr);

            REQUIRE(ptr.is_valid() == true);
        }
        REQUIRE(ptr.is_valid() == false);
    }

    SECTION("Is observed by ptr")
    {
        observable_object<TestingData> sut{"name", 2};

        {
            observer_ptr<TestingData> ptr;
            REQUIRE(sut.is_observed_by(ptr) == false);
            sut.register_observer(ptr);

            REQUIRE(sut.is_observed_by(ptr) == true);
        }
    }
}

} // namespace memory
} // namespace eul