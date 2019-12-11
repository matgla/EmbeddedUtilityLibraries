// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "catch.hpp"

#include "eul/function.hpp"

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

    void operator()(const int a) const
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
            REQUIRE(destructorCalled == 1);

            f2(11);
        }
        REQUIRE(value == 11);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 3);
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
            REQUIRE(destructorCalled == 1);

            f2(11);
        }
        REQUIRE(value == 11);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 3);
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
