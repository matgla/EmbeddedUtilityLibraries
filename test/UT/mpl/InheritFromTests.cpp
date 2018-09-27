#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/inherit_from.hpp"

namespace eul
{
namespace mpl
{

struct ChildOne
{
public:
    static constexpr int value()
    {
        return 1;
    }
};

struct ChildTwo
{
public:
    static constexpr int someNumber()
    {
        return 10;
    }
};

TEST_CASE("InheritFrom should", "[InheritFrom]")
{
    SECTION("Inherit from one type")
    {
        struct Parent : public eul::mpl::inherit_from<ChildOne>
        {
        };
        Parent p;

        REQUIRE(p.value() == 1);
    }

    SECTION("Inherit from multiple types")
    {
        struct Parent : public eul::mpl::inherit_from<ChildOne, ChildTwo>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }

    SECTION("Inherit from tuple")
    {
        struct Parent
            : public eul::mpl::inherit_from<std::tuple<ChildOne, ChildTwo>>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }
}

} // namespace mpl
} // namespace eul
