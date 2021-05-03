// This file is part of EUL project.
// Copyright (C) 2021 Mateusz Stadnik
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

#include <catch.hpp>

#include "eul/math/vector.hpp"

namespace eul::math 
{

TEST_CASE("VectorTests", "[MATH_TESTS]")
{
    SECTION("Adding vectors") 
    {
        using Vector2 = eul::math::vector<int, 2>;
        using Vector3 = eul::math::vector<float, 3>;

        Vector2 a = {1, 2};
        Vector2 b = {3, 4};

        REQUIRE((a + b) == Vector2{4, 6});

        Vector3 x = {1.5f, 2.5f, -3.0f};
        Vector3 y = {2.5f, 3.0f, 8.0f};

        REQUIRE((x + y) == Vector3{4.0f, 5.5f, 5.0f}); 
    }

    SECTION("Substract vectors")
    {
        using Vector2 = eul::math::vector<int, 2>;
        using Vector3 = eul::math::vector<float, 3>;

        Vector2 a = {1, 2};
        Vector2 b = {3, 4};

        REQUIRE((a - b) == Vector2{-2, -2});

        Vector3 x = {1.5f, 2.5f, -3.0f};
        Vector3 y = {2.5f, 3.0f, 8.0f};

        REQUIRE((x - y) == Vector3{-1.0f, -0.5f, -11.0f}); 
 
    }

    SECTION("Scalar multiplication")
    {
        using Vector2 = eul::math::vector<int, 3>;

        Vector2 x = {1, 2};
        Vector2 y = {3, -5};

        REQUIRE(x.scalar_mul(y) == -7); 
 
    }

}

} // namespace eul::math

