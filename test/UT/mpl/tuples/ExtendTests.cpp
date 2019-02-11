#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/tuples/extend.hpp"

namespace eul
{
namespace mpl
{
namespace tuples
{

TEST_CASE("Extend should", "[AddType]")
{
    SECTION("extend types")
    {
        using TwoTypesTuple = extend<std::tuple<int>>::with<double>::type;
        using FiveTypesTuple = extend<TwoTypesTuple>::with<double, char, long int>::type;

        REQUIRE(std::tuple_size<TwoTypesTuple>::value == 2);
        REQUIRE(std::tuple_size<FiveTypesTuple>::value == 5);
        REQUIRE(typeid(TwoTypesTuple).name()
                == typeid(std::tuple<int, double>).name());
        REQUIRE(typeid(FiveTypesTuple).name()
                == typeid(std::tuple<int, double, double, char, long int>).name());
    }
}

} // namespace tuples
} // namespace mpl
} // namespace eul
