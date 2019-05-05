#pragma once

#include <cstdint>
#include <utility>

namespace eul
{
namespace utils
{

int pow(int base, int index);
std::pair<uint16_t, uint16_t> floatToInts(float number, const uint8_t precision);

} // namespace utils
} // namespace eul
