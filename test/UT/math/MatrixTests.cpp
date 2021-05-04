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

#include <iostream>

#include "eul/math/matrix.hpp"

namespace eul::math 
{

TEST_CASE("MatrixTests", "[MATH_TESTS]")
{
    SECTION("Adding matrix") 
    {
        using matrix_2x2 = eul::math::matrix<int, 2, 2>;
        const matrix_2x2 a =
            {
                {1, 2},
                {3, 4}
            };

        const matrix_2x2 b = 
            {
                {5, 6},
                {7, 8}
            };


        REQUIRE((a + b) == matrix_2x2 {
                {6, 8},
                {10, 12}
        });

        REQUIRE(a == matrix_2x2 {
                {1, 2},
                {3, 4}
        });

        REQUIRE(b == matrix_2x2 {
                {5, 6},
                {7, 8}
        });

        matrix_2x2 c {
            {-10, -5},
            {10, 2}
        };

        c += { 
            {-5, 10},
            {2, 10} 
        };

        REQUIRE(c == matrix_2x2 { 
            { -15, 5 },
            {  12, 12}
        });
    }

    SECTION("Substract matrix")
    {
        using matrix_2x2 = eul::math::matrix<int, 2, 2>;
        const matrix_2x2 a =
            {
                {1, 2},
                {3, 4}
            };

        const matrix_2x2 b = 
            {
                {5, 6},
                {7, 8}
            };


        REQUIRE((a - b) == matrix_2x2 {
                {-4, -4},
                {-4, -4}
        });

        REQUIRE(a == matrix_2x2 {
                {1, 2},
                {3, 4}
        });

        REQUIRE(b == matrix_2x2 {
                {5, 6},
                {7, 8}
        });

        matrix_2x2 c {
            {-10, -5},
            {10, 2}
        };

        c -= { 
            {-5, 10},
            {2, 10} 
        };

        REQUIRE(c == matrix_2x2 { 
            { -5, -15 },
            {  8, -8}
        });
 
    }

    SECTION("Scalar multiplication")
    {
        using matrix_2x2 = eul::math::matrix<int, 2, 2>;
        const matrix_2x2 a =
            {
                {1, 2},
                {3, 4}
            };
        
        REQUIRE((a * 5) == matrix_2x2 {
                { 5, 10 },
                { 15, 20 }
            });

        matrix_2x2 b { 
            { -1, 2 },
            {-8, 9 }
        };

        b *= -3;

        REQUIRE(b == matrix_2x2 {
            { 3, -6 },
            {24, -27 }
        });
        
    }

    SECTION("Matrix multiplication")
    {
        using matrix_3x2 = eul::math::matrix<int, 2, 3>;
        using matrix_2x3 = eul::math::matrix<int, 3, 2>;
        using matrix_2x2 = eul::math::matrix<int, 2, 2>;
        const matrix_2x3 a = {
            {2, 1, 3},
            {-1, 2, 4}
        };
       
        const matrix_3x2 b = {
            {1, 3},
            {2, -2},
            {-1, 4}
        };


        REQUIRE((a * b) == matrix_2x2 {
            { 1, 16 },
            { -1, 9 }
        });

    }

}

} // namespace eul::math

