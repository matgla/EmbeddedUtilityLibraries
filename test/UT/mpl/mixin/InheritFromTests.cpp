#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/mixin/inherit_from.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename ParentType>
struct ChildOne
{
public:
    static constexpr int value()
    {
        return 1;
    }
};

template <typename ParentType>
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
        struct Parent : public eul::mpl::mixin::inherit_from<Parent, ChildOne>
        {
        };
        Parent p;

        REQUIRE(p.value() == 1);
    }

    SECTION("Inherit from multiple types")
    {
        struct Parent
            : public eul::mpl::mixin::inherit_from<Parent, ChildOne, ChildTwo>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }

    SECTION("inherit from tuple")
    {
        struct Parent : public eul::mpl::mixin::inherit_from<
                            std::tuple<ChildOne<Parent>, ChildTwo<Parent>>>
        {
        };

        Parent p;
        REQUIRE(p.value() == 1);
        REQUIRE(p.someNumber() == 10);
    }
}

} // namespace mixin
} // namespace mpl
} // namespace eul