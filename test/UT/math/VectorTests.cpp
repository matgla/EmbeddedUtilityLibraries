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

#include <catch2/catch_test_macros.hpp>

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

    SECTION("Access elements")
    {
        using Vector3 = eul::math::vector<int, 3>;

        Vector3 v{1, 2, 3};

        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }

    SECTION("Dot product")
    {
        using Vector2 = eul::math::vector<int, 2>;

        Vector2 x = {1, 2};
        Vector2 y = {3, -5};

        REQUIRE(x.dot(y) == -7); 
    
    }
    
    SECTION("Multiply vector and matrix")
    {
        using Vector2 = eul::math::vector<int, 2>;
        using Vector3 = eul::math::vector<int, 3>;
        using Matrix_3x2 = eul::math::matrix<int, 3, 2>;

        const auto m = Matrix_3x2 {
            { 1, 2, 4 },
            { 3, 4, 5 }
        };

        const auto v = Vector2 {1, 2};

        const Vector3 ans = v * m;

        REQUIRE(ans == Vector3{7, 10, 14});

        using Vector4 = eul::math::vector<int, 4>;
        using Matrix_4x4 = eul::math::matrix<int, 4, 4>;

        const Vector4 v2 = { 1, 2, 3, 1 };
        const Matrix_4x4 m2 = { 
            { 2, 0, 0, 0 },
            { 0, 4, 0, 0 },
            { 0, 0, 2, 8 },
            { 0, 0, -1, 0}
        };

        REQUIRE((v2 * m2) == Vector4{2, 8, 5, 24});
    }
}

} // namespace eul::math

