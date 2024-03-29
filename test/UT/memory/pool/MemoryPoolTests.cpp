// // This file is part of EUL project. This project is set of libraries useful for embedded development.
// // Copyright (C) 2019 Mateusz Stadnik
// //
// // This program is free software: you can redistribute it and/or modify
// // it under the terms of the GNU General Public License as published by
// // the Free Software Foundation, either version 3 of the License, or
// // (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful,
// // but WITHOUT ANY WARRANTY; without even the implied warranty of
// // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// // GNU General Public License for more details.
// //
// // You should have received a copy of the GNU General Public License
// // along with this program.  If not, see <https://www.gnu.org/licenses/>.

// #include "catch2/catch_test_macros.hpp"

// #include "eul/memory/pool/memory_pool.hpp"

// class ConstructorTester
// {
// public:
//     ConstructorTester()
//         : constructed_(true)
//     {
//     }

//     [[nodiscard]] constexpr bool constructed() const
//     {
//         return constructed_;
//     }

// private:
//     bool constructed_ = false;
// };

// struct AllocationTestObject
// {
//     int a;
//     double b;
//     char c;
//     long double d;
// };


// class DestructorTester // NOLINT(cppcoreguidelines-special-member-functions)
// {
// public:
//     explicit DestructorTester(bool* destructed) : destructed_(destructed)
//     {
//         (*destructed) = false;
//     }

//     ~DestructorTester()
//     {
//         (*destructed_) = true;
//     }

// private:
//     bool* destructed_;
// };

// TEST_CASE("MemoryPool should", "[MemoryPool]")
// {
//     SECTION("call constructor")
//     {
//         constexpr std::size_t memory_pool_size = 128;
//         eul::memory::pool::memory_pool<memory_pool_size, uint8_t> sut;
//         auto test = sut.allocate<ConstructorTester>();
//         REQUIRE(test->constructed());
//     }

// //     SECTION("allocate data")
// //     {
// //         eul::memory::pool::memory_pool<> sut;
// //         auto test = sut.allocate<AllocationTestObject>();
// //         REQUIRE(test != nullptr);
// //         constexpr int integer1 = 123;
// //         constexpr double double1 = -223.123;
// //         constexpr char char1 = 'a';
// //         constexpr long double ldouble1 = 1231231234412.123123123;
// //         constexpr int integer2 = -12344;
// //         constexpr double double2 = 123512.1235325;
// //         constexpr char char2 = 'c';
// //         constexpr long double ldouble2 = -1234566788.865432;
// //
// //         test->a = integer1;
// //         test->b = double1;
// //         test->c = char1;
// //         test->d = ldouble1;
// //         REQUIRE(test->a == integer1);
// //         REQUIRE(test->b == double1);
// //         REQUIRE(test->c == char1);
// //         REQUIRE(test->d == ldouble1);
// //
// //         auto test2 = sut.allocate<AllocationTestObject>();
// //         REQUIRE(test2 != nullptr);
// //         test2->a = integer2;
// //         test2->b = double2;
// //         test2->c = char2;
// //         test2->d = ldouble2;
// //         REQUIRE(test->a == integer1);
// //         REQUIRE(test->b == double1);
// //         REQUIRE(test->c == char1);
// //         REQUIRE(test->d == ldouble1);
// //
// //         REQUIRE(test2->a == integer2);
// //         REQUIRE(test2->b == double2);
// //         REQUIRE(test2->c == char2);
// //         REQUIRE(test2->d == ldouble2);
// //
// //         sut.deallocate(test);
// //         REQUIRE(test2->a == integer2);
// //         REQUIRE(test2->b == double2);
// //         REQUIRE(test2->c == char2);
// //         REQUIRE(test2->d == ldouble2);
// //
// //     }
// //
// //    SECTION("don't overflow buffer")
// //    {
// //        eul::memory::pool::memory_pool<65> sut;
// //        auto test = sut.allocate<AllocationTestObject>();
// //        REQUIRE(test != nullptr);
// //        constexpr int integer1 = 123;
// //        constexpr double double1 = -223.123;
// //        constexpr char char1 = 'a';
// //        constexpr long double ldouble1 = 1231231234412.123123123;
// //
// //        test->a = integer1;
// //        test->b = double1;
// //        test->c = char1;
// //        test->d = ldouble1;
// //        REQUIRE(test->a == integer1);
// //        REQUIRE(test->b == double1);
// //        REQUIRE(test->c == char1);
// //        REQUIRE(test->d == ldouble1);
// //
// //        auto test2 = sut.allocate<AllocationTestObject>();
// //        REQUIRE(test2 == nullptr);
// //        REQUIRE(test->a == integer1);
// //        REQUIRE(test->b == double1);
// //        REQUIRE(test->c == char1);
// //        REQUIRE(test->d == ldouble1);
// //    }
// //
// //    SECTION("Destroys object while deallocation")
// //    {
// //        // eul::memory_pool<uint8_t, 128> sut;
// //        // bool isObject1Destroyed = false;
// //        // bool isObject2Destroyed = false;
// //        // {
// //        //     auto obj1 = sut.allocate<DestructorTester>(isObject1Destroyed);
// //        //     auto obj2 = sut.allocate<DestructorTester>(isObject2Destroyed);
// //        //     sut.deallocate(obj1);
// //        //     sut.deallocate(obj2);
// //        // }
// //        // REQUIRE(isObject1Destroyed);
// //        // REQUIRE(isObject2Destroyed);
// //    }
// //
// //    SECTION("Best fit new object")
// //    {
// //        // b - free block ( sizeof(std::max_align_t), i.e 32bytes)
// //        // r - reserved block
// //        // step 0
// //        // [b b b b b b b b b b]
// //        // step 1: allocation of 1.5 blocks (a1)
// //        // [r r r b b b b b b b]
// //        // step 2: allocation of 3 blocks (a2)
// //        // [r r r r r r r b b b]
// //        // step 3: deallocation a1
// //        // [b b b r r r r b b b]
// //        // step 4: allocation of 1 block (a3)
// //        // [r r b r r r r b b b]
// //        // step 5: allocation of 2 blocks (a4)
// //        // [r r b r r r r r r r]
// //        // step 6: allocation of 1 block (a5)
// //        // -> fail
// //
// //
// //
// //
// //    }
// }
