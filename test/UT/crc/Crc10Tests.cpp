// This file is part of EmbeddedUtilityLibraries project.
// Copyright (C) 2021 Mateusz Stadnik
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

#include <cstdint> 
#include <vector>

#include "CrcTestBase.hpp"

#include <eul/crc/crc10.hpp>

namespace eul::crc
{

const static std::vector<std::vector<uint8_t>> test_data{
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39},
    {0x00},
    {0xff},
    {0x14},
    {0x2, 0xff, 0xff},
    {0x00, 0x00},
    {0xff, 0xff, 0xff, 0xff},
};

static_assert(std::is_same_v<Crc10, Crc10_ATM>, "Crc10 should be same as Crc10_ATM");
static_assert(std::is_same_v<Crc10_I_610, Crc10_ATM>, "Crc10_I_610 should be same as Crc10_ATM");
        
REGISTER_CRC_TEST(Crc10_ATM,        test_data, {0x199, 0x000, 0x0e1, 0x2a8, 0x32a, 0x000, 0x056});
REGISTER_CRC_TEST(Crc10_CDMA2000,   test_data, {0x233, 0x356, 0x300, 0x0d8, 0x083, 0x2f8, 0x1d0});
REGISTER_CRC_TEST(Crc10_GSM,        test_data, {0x12a, 0x3ff, 0x274, 0x1da, 0x3a7, 0x3ff, 0x07f});

} // namespace eul::crc

