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

#include <cstring>

#include "eul/utils/assert.hpp"
#include "eul/utils/math.hpp"

namespace eul::utils
{

void reverse(char* s)
{
    char* j = s + std::strlen(s) - 1; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    char c = '\0';

    while (s < j)
    {
        c    = *s;
        *s++ = *j; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        *j-- = c; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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

int writeToBufferAligned(char* buffer, int data, char suffix, uint8_t size, char prefix)
{
    int i = 0;
    constexpr int dec_base = 10;

    for (int tmp = data == 0 ? 1 : data; tmp < pow(dec_base, size - 1);)
    {
        tmp *= dec_base;
        buffer[i++] = prefix; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    i += utils::itoa(data, buffer + i); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    buffer[i++] = suffix; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return i;
}

int writeToBufferAligned(char* buffer, int data, char suffix)
{
    return writeToBufferAligned(buffer, data, suffix, 2, '0');
}

int formatTime(char* buffer, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_hour, ':'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    i += writeToBufferAligned(&buffer[i], t->tm_min, ':'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    i += writeToBufferAligned(&buffer[i], t->tm_sec, '\0'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return i;
}

int formatDate(char* buffer, std::tm* t)
{
    int i = 0;
    constexpr int year_offset = 1900;
    i += writeToBufferAligned(&buffer[i], t->tm_mday, '/'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    i += writeToBufferAligned(&buffer[i], t->tm_mon + 1, '/'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    i += writeToBufferAligned(&buffer[i], t->tm_year + year_offset, '\0'); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    return i;
}

void formatDateAndTime(char* buffer, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, t); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    buffer[i - 1] = ' '; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    i += formatTime(buffer + i, t); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

} // namespace eul::utils
