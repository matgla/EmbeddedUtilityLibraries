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

#include "eul/utils/math.hpp"

#include <cmath>

namespace eul::utils
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


std::pair<uint16_t, uint16_t> floatToInts(float number, uint8_t precision)
{
    auto high = static_cast<uint16_t>(std::floor(number));
    uint16_t low = 0;
    auto floatingPoint = number - static_cast<float>(high);
    constexpr int base = 10;
    auto multiplier    = static_cast<float>(pow(base, precision));\
    constexpr float epsilion = 0.1;
    if (floatingPoint < epsilion)
    {
        low = static_cast<uint16_t>(std::round(floatingPoint * base) / base * base);
    }
    else
    {
        low = static_cast<uint16_t>(std::round(floatingPoint * multiplier));
    }

    return std::make_pair(high, low);
}

} // namespace eul::utils
