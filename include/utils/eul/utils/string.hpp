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

#pragma once

#include <algorithm>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <type_traits>
#include <string_view>

#include <span>

namespace eul::utils
{

char int_to_char(int n);

template <int base_n = 10>
inline std::span<char>::size_type itoa(auto n, std::span<char> s)
{
    using T = std::decay_t<decltype(n)>;
    static_assert(std::is_arithmetic_v<decltype(n)>, "Type provided for serialize isn't arithmetic");
    static_assert(base_n >= 1 && base_n <= 16, "Base must be passed in range <1:16>");
    std::span<char>::size_type i = 0;
    T sign = n;

    if (sign < 0)
    {  /* record sign */
        n = -n; /* make n positive */
    }

    do
    {                                   /* generate digits in reverse order */
        s[i++] = int_to_char(n % base_n); /* get next digit */ // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    } while ((n /= base_n) > 0);        /* delete it */
    if (sign < 0)
    {
        s[i++] = '-'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    s[i] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    std::reverse(s.begin(), s.begin() + static_cast<long>(i));

    return 0;
}

template <typename T>
inline int strlen(const std::span<T>& data)
{
    for (typename std::span<T>::size_type i = 0; i < data.size(); ++i)
    {
        if (data[i] == 0)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

} // namespace eul::utils
