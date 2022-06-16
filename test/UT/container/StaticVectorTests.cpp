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

#include <algorithm>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include "eul/container/static_vector.hpp"


TEST_CASE("Static vector should", "[StaticVectorTests]")
{
    SECTION("push_back elements")
    {
        eul::container::static_vector<int, 4> sut;

        REQUIRE(sut.empty());
        sut.push_back(1);
        sut.push_back(2);
        sut.push_back(3);
        sut.push_back(4);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut[0] == 1);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 3);
        REQUIRE(sut[3] == 4);
    }

    SECTION("copy elements using std algorithm")
    {
        std::vector<uint8_t> data{0, 1, 2};
        constexpr std::size_t size = 8;
        eul::container::static_vector<uint8_t, size> sut;

        std::copy(data.begin(), data.end(), std::back_inserter(sut));

        REQUIRE(sut.size() == 3);
        REQUIRE(sut[0] == 0);
        REQUIRE(sut[1] == 1);
        REQUIRE(sut[2] == 2);

        std::copy(data.begin(), data.end(), std::back_inserter(sut));

        REQUIRE(sut.size() == 6);
        REQUIRE(sut[0] == 0);
        REQUIRE(sut[1] == 1);
        REQUIRE(sut[2] == 2);
        REQUIRE(sut[3] == 0);
        REQUIRE(sut[4] == 1);
        REQUIRE(sut[5] == 2);
    }

    SECTION("returns maximal size")
    {
        eul::container::static_vector<uint8_t, 4> sut;
        constexpr std::size_t changed_size = 8;
        eul::container::static_vector<uint8_t, changed_size> sut2;

        REQUIRE(sut.max_size() == 4);
        REQUIRE(sut2.max_size() == changed_size);
    }

    SECTION("copy vectors")
    {
        eul::container::static_vector<uint8_t, 3> sut;
        eul::container::static_vector<uint8_t, 2> other{3, 4};

        sut = other;
        REQUIRE(sut.size() == 2);
        REQUIRE(sut[0] == 3);
        REQUIRE(sut[1] == 4);
    }

    SECTION("assign values")
    {
        eul::container::static_vector<int, 4> sut;
        sut.assign<4>(2);

        REQUIRE(sut.size() == 4);
        REQUIRE(sut[0] == 2);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 2);
        REQUIRE(sut[3] == 2);
    }

    SECTION("initalizes with initializer list")
    {
        const eul::container::static_vector<uint8_t, 4> sut{1, 2, 3, 4};
        const eul::container::static_vector<uint8_t, 4> sut2{1, 2, 3, 4};
        const eul::container::static_vector<uint8_t, 4> sut3({1, 2, 3, 4});

        REQUIRE(sut[0] == 1);
        REQUIRE(sut[1] == 2);
        REQUIRE(sut[2] == 3);
        REQUIRE(sut[3] == 4);
        REQUIRE(sut.size() == 4);

        REQUIRE(sut2[0] == 1);
        REQUIRE(sut2[1] == 2);
        REQUIRE(sut2[2] == 3);
        REQUIRE(sut2[3] == 4);
        REQUIRE(sut2.size() == 4);

        REQUIRE(sut3[0] == 1);
        REQUIRE(sut3[1] == 2);
        REQUIRE(sut3[2] == 3);
        REQUIRE(sut3[3] == 4);
        REQUIRE(sut3.size() == 4);
    }

    SECTION("access back element")
    {
        eul::container::static_vector<int, 2> sut{1};

        REQUIRE(sut.back() == 1);
        REQUIRE(sut.size() == 1);

        constexpr int test_value = 15;
        sut.push_back(test_value);
        REQUIRE(sut.back() == test_value);
        REQUIRE(sut.size() == 2);
    }

    SECTION("access front element")
    {
        eul::container::static_vector<int, 2> sut{1};

        REQUIRE(sut.front() == 1);
        REQUIRE(sut.size() == 1);

        constexpr int test_value = 15;
        sut.push_back(test_value);
        REQUIRE(sut.front() == 1);
        REQUIRE(sut.size() == 2);
    }

    SECTION("pop back element")
    {
        eul::container::static_vector<int, 2> sut{1};

        REQUIRE(sut.pop_back() == 1);
        REQUIRE(sut.empty());

        constexpr int test_value = 15;
        sut.push_back(test_value);
        REQUIRE(sut.pop_back() == test_value);
        REQUIRE(sut.empty());
    }

    SECTION("access elements via at")
    {
        eul::container::static_vector<int, 2> sut{1, 2};

        REQUIRE(sut.at<0>() == 1);
        REQUIRE(sut.at<1>() == 2);
    }

    SECTION("clear")
    {
        eul::container::static_vector<int, 2> sut{1, 2};

        REQUIRE(sut.size() == 2);

        sut.clear();
        REQUIRE(sut.empty());
    }

    SECTION("return iterator to begin")
    {
        eul::container::static_vector<int, 2> sut{1, 2};
        auto it = sut.begin();

        REQUIRE(*it == 1);
        ++it; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        REQUIRE(*it == 2);

        constexpr int test_value = 15;
        *it = test_value;
        REQUIRE(sut.back() == test_value);
    }

    SECTION("return const iterator to begin")
    {
        using Container = eul::container::static_vector<int, 2>;
        Container sut{1, 2};
        Container::const_iterator it = sut.begin(); // NOLINT(modernize-use-auto)

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
    }

    SECTION("return iterator to end")
    {
        eul::container::static_vector<int, 2> sut{1, 2};
        auto it = sut.end(); // NOLINT(readability-qualified-auto)

        REQUIRE(*(--it) == 2);
        REQUIRE(*(--it) == 1);

        constexpr int test_value = 15;
        *it = test_value;
        REQUIRE(sut.front() == test_value);
    }

    SECTION("return const iterator to end")
    {
        using Container = eul::container::static_vector<int, 2>;
        Container sut{1, 2};
        Container::const_iterator it = sut.end(); // NOLINT(modernize-use-auto)

        REQUIRE(*(--it) == 2);
        REQUIRE(*(--it) == 1);
    }
    SECTION("erase elements")
    {
        using Container = eul::container::static_vector<int, 4>;
        Container sut{1, 2, 3, 4};

        REQUIRE(sut == Container{1, 2, 3, 4});
        sut.erase(sut.begin() + 2);
        REQUIRE(sut == Container{1, 2, 4});
        sut.erase(sut.end());
        REQUIRE(sut == Container{1, 2, 4});
        sut.erase(sut.end() - 1);
        REQUIRE(sut == Container{1, 2});
        sut.erase(sut.begin());
        REQUIRE(sut == Container{2});
        sut.erase(sut.begin());
        REQUIRE(sut.empty());
        sut.erase(sut.begin());
        REQUIRE(sut.empty());
    }
}
