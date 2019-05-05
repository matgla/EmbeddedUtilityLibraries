#include "eul/utils/math.hpp"

#include <cmath>
#include <utility>

namespace eul
{
namespace utils
{

int pow(int base, int index)
{
    int answer = base;
    for (int i = 1; i < index; ++i)
    {
        answer *= base;
    }

    return answer;
}


std::pair<uint16_t, uint16_t> floatToInts(float number, const uint8_t precision)
{
    uint16_t high = std::floor(number);
    uint16_t low;
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

    return std::make_pair(high, low);
}

} // namespace utils
} // namespace eul
