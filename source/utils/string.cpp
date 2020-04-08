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

#include "eul/assert.hpp"
#include "eul/utils/math.hpp"

namespace eul
{
namespace utils
{

void reverse(char* s)
{
    char* j = s + std::strlen(s) - 1;
    char c;

    j = s + std::strlen(s) - 1;
    while (s < j)
    {
        c    = *s;
        *s++ = *j;
        *j-- = c;
    }
}

char int_to_char(int n)
{
    if (n > 9)
    {
        return static_cast<char>(n - 10 + 'a');
    }
    else
    {
        return static_cast<char>(n + '0');
    }
}

int writeToBufferAligned(char* buffer, int data, char suffix, uint8_t size, char prefix)
{
    int i = 0;
    for (int tmp = data == 0 ? 1 : data; tmp < pow(10, size - 1);)
    {
        tmp *= 10;
        buffer[i++] = prefix;
    }
    i += utils::itoa(data, buffer + i);
    buffer[i++] = suffix;
    return i;
}


int formatTime(char* buffer, int bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_hour, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_min, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_sec, '\0');
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

int formatDate(char* buffer, int bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_mday, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_mon + 1, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_year + 1900, '\0');

    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

void formatDateAndTime(char* buffer, int bufferSize, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, bufferSize - i, t);
    buffer[i - 1] = ' ';
    i += formatTime(buffer + i, bufferSize - i, t);
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
}

} // namespace utils
} // namespace eul
