#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/mixin/access.hpp"
#include "eul/mpl/mixin/base.hpp"
#include "eul/mpl/mixin/data.hpp"
#include "eul/mpl/mixin/object.hpp"

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
struct has_set_a_method : std::false_type
{
};

template <typename T>
concept bool has_a_method_concept = requires(T a)
{
    // clang-format off
    {a.setA(int{})}->void;
    // clang-format on
};

template <has_a_method_concept T>
struct has_set_a_method<T> : std::true_type
{
};

struct DataForC;
struct Data2ForC;

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

    int data1()
    {
        auto data = access<BaseType>(this);
        return data[type<DataForC>{}].a_;
    }

    int data2()
    {
        auto data = access<BaseType>(this);
        return data[type<Data2ForC>{}].a_;
    }

    void setAllA(int a)
    {
        auto data = access<BaseType>(this);
        data.for_each(ability<has_set_a_method>{},
                      [a](auto& data) { data.setA(a); });
    }

    void setDifferentAllA(int a)
    {
        a_        = a;
        auto data = access<BaseType>(this);
        data.for_each(ability<has_set_a_method>{}, [this](auto& data) {
            data.setA(a_);
            a_ += 10;
        });
    }

    int a_;
};

struct DataForC
{
    DataForC()                = default;
    DataForC(const DataForC&) = delete;
    DataForC& operator=(const DataForC&) = delete;
    DataForC(DataForC&&)                 = default;
    DataForC& operator=(DataForC&&) = default;
    void setA(int a)
    {
        a_ = a;
    }

    int a_ = 2;
};

struct Data2ForC
{
    void setA(int a)
    {
        a_ = a;
    }

    int a_ = 5;
};

TEST_CASE("Mixin should", "[Mixin]")
{
    SECTION("Create object")
    {
        auto mixedObject
            = compose<base<InterfaceA, InterfaceB>::type>::with_data(DataA{},
                                                                     DataB{});
        REQUIRE(mixedObject.callA() == 2);
        REQUIRE(mixedObject.callB() == 3);

        mixedObject.setA(10);
        REQUIRE(mixedObject.callA() == 10);
        REQUIRE(mixedObject.callB() == 3);
    }

    SECTION("set for ability")
    {
        auto mixedObject
            = compose<base<InterfaceC>::type>::with_data(DataB{}, DataForC{});
        REQUIRE(mixedObject.callA() == 2);
        mixedObject.setA(15);
        REQUIRE(mixedObject.callA() == 15);
        REQUIRE(mixedObject.returnA() == 15);
    }

    SECTION("for each ability")
    {
        auto mixedObject = compose<base<InterfaceC>::type>::with_data(
            DataForC{}, Data2ForC{});
        REQUIRE(mixedObject.data1() == 2);
        REQUIRE(mixedObject.data2() == 5);

        mixedObject.setAllA(11);
        REQUIRE(mixedObject.data1() == 11);
        REQUIRE(mixedObject.data2() == 11);

        mixedObject.setDifferentAllA(40);

        REQUIRE(mixedObject.data1() == 40);
        REQUIRE(mixedObject.data2() == 50);
    }
}

} // namespace mixin
} // namespace mpl
} // namespace eul
