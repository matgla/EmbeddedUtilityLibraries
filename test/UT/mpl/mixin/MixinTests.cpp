#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/mixin/interface.hpp"
#include "eul/mpl/mixin/mixin.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

struct DataA;

struct DataB;

template <typename BaseType>
struct InterfaceA
{
    int callA()
    {
        auto data = access<BaseType>(this);
        return data.template get<DataA>().a;
    }

    void setA(int a)
    {
        auto data                    = access<BaseType>(this);
        data.template get<DataA>().a = a;
    }
};

template <typename BaseType>
struct InterfaceB
{
    int callB()
    {
        return 3;
    }
};

struct DataA
{
    int a = 2;
};

struct DataB
{
    int b;
};


template <typename T>
struct has_set_a_method
{
    constexpr static bool value = requires(T a)
    {
        // clang-format off
        {a.setA(int{})}->void;
        // clang-format on
    };
};

template <typename BaseType>
struct InterfaceC
{
    void setA(int a)
    {
        auto data = access<BaseType>(this);
        data.template get_by_ability<has_set_a_method>().setA(a);
    }

    int callA()
    {
        auto data = access<BaseType>(this);
        return data.template get_by_ability<has_set_a_method>().a_;
    }

    int returnA()
    {
        auto data = access<BaseType>(this);
        return data[ability<has_set_a_method>{}].a_;
    }
};

struct DataForC
{
    void setA(int a)
    {
        a_ = a;
    }

    int a_ = 2;
};

TEST_CASE("Mixin should", "[Mixin]")
{
    SECTION("Create object")
    {
        auto object
            = mixin<interface<InterfaceA>::type, interface<InterfaceB>::type,
                    data<DataA>::type, data<DataB>::type>();
        REQUIRE(object.callA() == 2);
        REQUIRE(object.callB() == 3);

        object.setA(10);
        REQUIRE(object.callA() == 10);
        REQUIRE(object.callB() == 3);
    }

    SECTION("set for ability")
    {
        auto object
            = mixin<interface<InterfaceC>::type, data<DataForC>::type>();
        REQUIRE(object.callA() == 2);
        object.setA(15);
        REQUIRE(object.callA() == 15);
        REQUIRE(object.returnA() == 15);
    }
}

} // namespace mixin
} // namespace mpl
} // namespace eul
