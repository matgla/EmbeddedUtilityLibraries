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
    TestFunctor(int* constructorCalled, int* destructorCalled, int* functionCalled) // NOLINT(readability-non-const-parameter)
        : constructorCalled_(*constructorCalled)
        , destructorCalled_(*destructorCalled)
        , functionCalled_(*functionCalled)
    {
        constructorCalled_++;
    }

    ~TestFunctor()
    {
        destructorCalled_++;
    }

    TestFunctor(TestFunctor&&) = default;
    TestFunctor(const TestFunctor&) = default;
    TestFunctor& operator=(TestFunctor&&) = delete;
    TestFunctor& operator=(const TestFunctor&) = delete;

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
        constexpr int initial_expected_value = 15;
        int expectedValue        = initial_expected_value;
        constexpr int otherValue = -9999999;

        constexpr std::size_t function_size = 8;
        eul::function<void(int), function_size> f1([&expectedValue](int a) { expectedValue = otherValue + a; });
        constexpr int number_to_add_1 = 10;
        f1(number_to_add_1);
        REQUIRE(expectedValue == (otherValue + number_to_add_1));
        constexpr int number_to_add_2 = -100;
        f1(number_to_add_2);
        REQUIRE(expectedValue == (otherValue + number_to_add_2));
    }

    SECTION("change to another function")
    {
        constexpr int initial_expected_value = 15;
        int expectedValue = initial_expected_value;
        constexpr int otherValue    = -9999999;

        constexpr std::size_t function_size = 8;
        eul::function<int(int), function_size> f1([&expectedValue](int a) { expectedValue = otherValue + a; return expectedValue; });
        constexpr int number_to_add = 10;
        f1(number_to_add);
        REQUIRE(expectedValue == (otherValue + number_to_add));
        f1 = [](int a) { return a; };
        constexpr int test_number_1 = 15;
        constexpr int test_number_2 = -5;
        REQUIRE(f1(test_number_1) == test_number_1);
        REQUIRE(f1(test_number_2) == test_number_2);
    }

    SECTION("Functor")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        constexpr int test_value = 1234567;
        {
            eul::function<void(int), sizeof(void*) * 2> f1(TestFunctor(&constructorCalled, &destructorCalled, &value));

            f1(test_value);

            REQUIRE(value == test_value);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 1);
        }
        REQUIRE(value == test_value);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 2);
    }

    SECTION("Copy")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        constexpr int test_number = 1234567;
        constexpr int test_number_2 = 11;

        {
            eul::function<void(int), sizeof(void*)*2> f1(TestFunctor(&constructorCalled, &destructorCalled, &value));
            eul::function<void(int), sizeof(void*)*2> f2(f1);
            f1(test_number);

            REQUIRE(value == test_number);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 1);


            f2(test_number_2);
        }
        REQUIRE(value == test_number_2);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 3);
    }

    SECTION("Copy by operator")
    {
        int constructorCalled = 0;
        int destructorCalled  = 0;
        int value             = 0;
        constexpr int test_number = 1234567;
        constexpr int test_number_2 = 11;

        {
            eul::function<void(int), sizeof(void*)*2> f1(TestFunctor(&constructorCalled, &destructorCalled, &value));
            eul::function<void(int), sizeof(void*)*2> f2 = f1;

            f1(test_number);

            REQUIRE(value == test_number);
            REQUIRE(constructorCalled == 1);
            REQUIRE(destructorCalled == 1);

            f2(test_number_2);
        }
        REQUIRE(value == test_number_2);
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
        constexpr int test_number = 1234567;
        constexpr int test_number_2 = 1112;

        {
            eul::function<void(int), sizeof(void*)*2> f1(TestFunctor(&constructorCalled, &destructorCalled, &value));

            {
                f1(test_number);

                REQUIRE(value == test_number);
                REQUIRE(constructorCalled == 1);
                REQUIRE(destructorCalled == 1);
            }
            {
                f1 = TestFunctor(&constructorCalled2, &destructorCalled2, &value2);
                f1(test_number_2);
                REQUIRE(value2 == test_number_2);
                REQUIRE(constructorCalled2 == 1);
                REQUIRE(destructorCalled2 == 1);
            }
        }
        REQUIRE(value == test_number);
        REQUIRE(constructorCalled == 1);
        REQUIRE(destructorCalled == 2);
        REQUIRE(value2 == test_number_2);
        REQUIRE(constructorCalled2 == 1);
        REQUIRE(destructorCalled2 == 2);
    }
}
