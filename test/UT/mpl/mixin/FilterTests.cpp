#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/mixin/filter.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename... T>
struct interface
{
    using Type = std::tuple<T...>;
};

struct WithInterface
{
};

struct WithInterface2
{
};

struct WithoutInterface
{
};

template <typename T>
struct is_interface : std::false_type
{
};


template <typename... T>
struct is_interface<interface<T...>> : std::true_type
{
};


TEST_CASE("Filter should", "[Filter]")
{
    SECTION("filter integers")
    {
        using IntegerTuple = typename filter<std::is_integral, int, long double,
                                             std::string, long int>::type;

        REQUIRE(std::tuple_size<IntegerTuple>::value == 2);
        REQUIRE(typeid(IntegerTuple).name()
                == typeid(std::tuple<int, long int>).name());
    }

    SECTION("filter by own predicate")
    {
        using Interfaces =
            typename filter<is_interface, interface<WithInterface>,
                            interface<WithInterface>, interface<WithInterface2>,
                            WithInterface, WithoutInterface>::type;

        REQUIRE(typeid(Interfaces).name()
                == typeid(std::tuple<interface<WithInterface>,
                                     interface<WithInterface>,
                                     interface<WithInterface2>>)
                       .name());
    }
}

} // namespace mixin
} // namespace mpl
} // namespace eul
