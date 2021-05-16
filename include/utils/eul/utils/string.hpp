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

#include <cstdint>
#include <cstring>
#include <ctime>
#include <type_traits>

#include <span>

namespace eul::utils
{

void reverse(std::span<char> s);

char int_to_char(int n);

template <typename T>
inline T itoa(T n, std::span<char> s, int base_n)
{
    static_assert(std::is_arithmetic<T>::value, "Type provided for serialize isn't arithmetic");
    T i = 0;
    T sign = n;

    if (sign < 0)
    {  /* record sign */
        n = -n; /* make n positive */
    }

    i = 0;
    do
    {                                   /* generate digits in reverse order */
        s[i++] = int_to_char(n % base_n); /* get next digit */ // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    } while ((n /= base_n) > 0);        /* delete it */
    if (sign < 0)
    {
        s[i++] = '-'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    s[i] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    reverse(s);
    return i;
}

template <typename T>
inline T itoa(T n, std::span<char> s)
{
    constexpr int base = 10;
    return itoa<T>(n, s, base);
}

template <typename T>
inline int strlen(const std::span<T>& data)
{
    for (typename std::span<T>::index_type i = 0; i < data.size(); ++i)
    {
        if (data[i] == 0)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

} // namespace eul::utils
