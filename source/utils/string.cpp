#include "eul/utils/string.hpp"

#include <cstring>

#include "eul/assert.hpp"
#include "eul/utils/math.hpp"

namespace eul
{
namespace utils
{

// void reverse(char* s)
// {
//     char* j = s + std::strlen(s) - 1;
//     int c;
// 
//     j = s + std::strlen(s) - 1;
//     while (s < j)
//     {
//         c    = *s;
//         *s++ = *j;
//         *j-- = c;
//     }
// }
// 
// char int_to_char(int n)
// {
//     if (n > 9)
//     {
//         return n - 10 + 'a';
//     }
//     else
//     {
//         return n + '0';
//     }
// }

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


int formatTime(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_hour, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_min, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_sec, '\0');
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

int formatDate(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_mday, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_mon + 1, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_year + 1900, '\0');

    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

void formatDateAndTime(char* buffer, const uint8_t bufferSize, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, bufferSize - i, t);
    buffer[i - 1] = ' ';
    i += formatTime(buffer + i, bufferSize - i, t);
    EUL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
}

} // namespace utils
} // namespace eul
