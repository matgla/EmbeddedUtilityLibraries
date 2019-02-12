#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <type_traits>
#include <utility>

#include <gsl/span>

#include "eul/assert.hpp"


// clang-format off
#define UNUSED1(x) (void)(x)

#define UNUSED2(x, y) \
    UNUSED1(x);       \
    UNUSED1(y)

#define UNUSED3(x, y, z) \
    UNUSED2(y, z);       \
    UNUSED1(x)

#define UNUSED4(x, y, z, e) \
    UNUSED3(y, z, e);       \
    UNUSED1(x)

#define UNUSED5(x, y, z, e, f) \
    UNUSED4(y, z, e, f);       \
    UNUSED1(x)

#define UNUSED6(x, y, z, e, f, g) \
    UNUSED5(y, z, e, f, g);       \
    UNUSED1(x)

#define UNUSED7(x, y, z, e, f, g, h) \
    UNUSED6(y, z, e, f, g, h);       \
    UNUSED1(x)

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1)

#define ALL_UNUSED_IMPL_(nargs) UNUSED##nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define UNUSED(...) ALL_UNUSED_IMPL(VA_NUM_ARGS(__VA_ARGS__)) (__VA_ARGS__)
// clang-format on

namespace eul
{

/*
** reverse string in place
*/
inline void reverse(char* s)
{
    char* j;
    int c;

    j = s + strlen(s) - 1;
    while (s < j)
    {
        c    = *s;
        *s++ = *j;
        *j-- = c;
    }
}

inline char getNumber(int n)
{
    if (n > 9)
    {
        return n - 10 + 'a';
    }
    else
    {
        return n + '0';
    }
}

namespace utils
{
inline int pow(int base, int index)
{
    int answer = base;
    for (int i = 1; i < index; ++i)
    {
        answer *= base;
    }

    return answer;
}

template <typename T>
inline T itoa(T n, char* s, int base_n = 10)
{
    static_assert(std::is_arithmetic<T>::value, "Type provided for serialize isn't arithmetic");
    T i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {                                   /* generate digits in reverse order */
        s[i++] = getNumber(n % base_n); /* get next digit */
    } while ((n /= base_n) > 0);        /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return i;
}

inline std::pair<uint16_t, uint16_t> floatToInts(float number, const uint8_t precision)
{
    uint16_t high;
    uint16_t low;
    high                = std::floor(number);
    float floatingPoint = number - high;
    int multiplier      = pow(10, precision);
    if (floatingPoint < 0.1)
    {
        low = std::round(floatingPoint * 10) / 10 * 10;
    }
    else
    {
        low = std::round(floatingPoint * multiplier);
    }


    return std::pair<uint16_t, uint16_t>(high, low);
}

inline int writeToBufferAligned(char* buffer, int data, char suffix, uint8_t size = 2, char prefix = '0')
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


inline int formatTime(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_hour, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_min, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_sec, '\0');
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

inline int formatDate(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_mday, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_mon + 1, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_year + 1900, '\0');

    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

inline void formatDateAndTime(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, bufferSize - i, t);
    buffer[i - 1] = ' ';
    i += formatTime(buffer + i, bufferSize - i, t);
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
}

template <typename T>
inline int strlen(const gsl::span<T>& data)
{
    for (typename gsl::span<T>::index_type i = 0; i < data.size(); ++i)
    {
        if (data[i] == 0)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

} // namespace utils
} // namespace eul
