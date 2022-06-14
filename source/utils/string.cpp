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

#include "eul/utils/string.hpp"

#include <algorithm>
#include <cstring>

#include "eul/utils/assert.hpp"
#include "eul/utils/math.hpp"

namespace eul::utils
{

void reverse(std::span<char> str)
{
    if (str.empty())
    {
        return;
    }

}

char int_to_char(int n)
{
    constexpr int is_not_single_digit_check = 9;
    if (n > is_not_single_digit_check)
    {
        constexpr int dec_base = 10;
        return static_cast<char>(n - dec_base + 'a');
    }

    return static_cast<char>(n + '0');
}

} // namespace eul::utils
