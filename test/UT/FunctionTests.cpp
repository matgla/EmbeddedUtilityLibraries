#include "catch.hpp"

#include "eul/function.hpp"

namespace msgui
{

class TestFunctor
{
public:
    TestFunctor(int& constructorCalled, int& destructorCalled, int& functionCalled)
        : constructorCalled_(constructorCalled), destructorCalled_(destructorCalled), functionCalled_(functionCalled)
    {
        constructorCalled_++;
    }

    ~TestFunctor()
    {
        destructorCalled_++;
    }

    void operator()(int a)
    {
        functionCalled_ = a;
    }

private:
    int& constructorCalled_;
    int& destructorCalled_;
    int& functionCalled_;
};

TEST_CASE("Function test", "[FunctionTests]")
{
    SECTION("return value")
    {
        constexpr int expectedValue = 15;
        constexpr int otherValue    = -9999999;

        eul::function<int(), 1> f1([]() { return expectedValue; });
        REQUIRE(f1() == expectedValue);

        eul::function<int(), 1> f2([]() { return otherValue; });
        REQUIRE(f2() == otherValue);
    }

    SECTION("capture arguments")
    {
        int expectedValue        = 15;
        constexpr int otherValue = -9999999;

        eul::function<void(int), 8> f1([&expectedValue, otherValue](int a) { expectedValue = otherValue + a; });
        f1(10);
        REQUIRE(expectedValue == (otherValue + 10));
        f1(-100);
        REQUIRE(expectedValue == (otherValue - 100));
    }

    SECTION("change to another function")
    {
        int expectedValue = 15;
        int otherValue    = -9999999;

        eul::function<int(int), 8> f1([&expectedValue, otherValue](int a) { expectedValue = otherValue + a; return expectedValue; });
        f1(10);
        REQUIRE(expectedValue == (otherValue + 10));
        f1 = [](int a) { return a; };
        REQUIRE(f1(15) == 15);
        REQUIRE(f1(-5) == -5);
    }

    SECTION("Functor")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        {
            eul::function<void(int), 16> f1(TestFunctor(constructorCalled, destructorCalled, value));

            f1(1234567);

            REQUIRE(value == 1234567);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 1);
        }
        REQUIRE(value == 1234567);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 2);
    }

    SECTION("Copy")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        {
            eul::function<void(int), 16> f1(TestFunctor(constructorCalled, destructorCalled, value));
            eul::function<void(int), 16> f2(f1);
            f1(1234567);

            REQUIRE(value == 1234567);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 2);

            f2(11);
        }
        REQUIRE(value == 11);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 4);
    }

    SECTION("Copy by operator")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        {
            eul::function<void(int), 16> f1(TestFunctor(constructorCalled, destructorCalled, value));
            eul::function<void(int), 16> f2 = f1;
            f1(1234567);

            REQUIRE(value == 1234567);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 2);

            f2(11);
        }
        REQUIRE(value == 11);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 4);
    }

    SECTION("Copy by operator")
    {
        int constructorCalled  = 0;
        int destructorCalled   = 0;
        int value              = 0;
        int constructorCalled2 = 0;
        int destructorCalled2  = 0;
        int value2             = 0;
        {
            eul::function<void(int), 16> f1(TestFunctor(constructorCalled, destructorCalled, value));

            {
                f1(1234567);

                REQUIRE(value == 1234567);
                REQUIRE(constructorCalled == 1);
                REQUIRE(destructorCalled == 1);
            }
            {
                f1 = TestFunctor(constructorCalled2, destructorCalled2, value2);
                f1(1112);
                REQUIRE(value2 == 1112);
                REQUIRE(constructorCalled2 == 1);
                REQUIRE(destructorCalled2 == 1);
            }
        }
        REQUIRE(value == 1234567);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 2);
        REQUIRE(value2 == 1112);
        REQUIRE(constructorCalled2 == 1);
        REQUIRE(destructorCalled2 == 2);
    }
}

} // namespace msgui