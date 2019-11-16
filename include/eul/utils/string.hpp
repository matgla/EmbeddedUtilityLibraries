#pragma once

#include <cstdint>
#include <ctime>
#include <type_traits>
#include <cstring>

#include <gsl/span>

namespace eul
{
namespace utils
{

void reverse(char* s);

char int_to_char(int n);

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
        s[i++] = int_to_char(n % base_n); /* get next digit */
    } while ((n /= base_n) > 0);        /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return i;
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

int writeToBufferAligned(char* buffer, int data, char suffix, uint8_t size = 2, char prefix = '0');
int formatTime(char* buffer, const uint8_t bufferSize, std::tm* t);
int formatDate(char* buffer, const uint8_t bufferSize, std::tm* t);
void formatDateAndTime(char* buffer, const uint8_t bufferSize, std::tm* t);

} // namespace utils
} // namespace eul
