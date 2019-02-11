#include <string>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/types/bind_type.hpp"
#include "eul/mpl/types/get_index_of_binded_key.hpp"

namespace eul
{
namespace mpl
{
namespace types
{

TEST_CASE("GetIndexOfBindedKey should", "[GetIndexOfBindedKey]")
{
    SECTION("Get index of binded key in tuple")
    {
        class A;
        class AI{};

        class B;
        class BI{};

        class C;
        class CI{};

        auto binded = std::make_tuple(
            bind_type<A>::to(AI{}),
            bind_type<B>::to(BI{}),
            bind_type<C>::to(CI{}));

        class D;

        using BindedType = decltype(binded);

        REQUIRE(tuple_index_getter<BindedType>::by_key<A>() == 0);
        REQUIRE(tuple_index_getter<BindedType>::by_key<B>() == 1);
        REQUIRE(tuple_index_getter<BindedType>::by_key<C>() == 2);

        REQUIRE(std::tuple_size<BindedType>::value == 3);
        REQUIRE(tuple_index_getter<BindedType>::by_key<D>() == -1);

        REQUIRE(get_index_from_tuple_by_key<A>(binded) == 0);
        REQUIRE(get_index_from_tuple_by_key<B>(binded) == 1);
        REQUIRE(get_index_from_tuple_by_key<C>(binded) == 2);

        REQUIRE(std::tuple_size<BindedType>::value == 3);
        REQUIRE(get_index_from_tuple_by_key<D>(binded) == -1);
    }
}

} // namespace types
} // namespace mpl
} // namespace eul
