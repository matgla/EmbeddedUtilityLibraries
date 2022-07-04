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

#include <eul/crc/crc6.hpp>

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

static_assert(std::is_same_v<Crc6_ITU, Crc6_G_704>, "Crc6_ITU should be same as Crc6_G_704");
        
REGISTER_CRC_TEST(Crc6_CDMA2000_A,  test_data, {0x0d});
REGISTER_CRC_TEST(Crc6_CDMA2000_B,  test_data, {0x3b});
REGISTER_CRC_TEST(Crc6_DARC,        test_data, {0x26, 0x00, 0x11, 0x2e, 0x26, 0x00, 0x1d});
REGISTER_CRC_TEST(Crc6_G_704,       test_data, {0x06, 0x00, 0x2c, 0x37, 0x1c, 0x00, 0x04});
REGISTER_CRC_TEST(Crc6_GSM,         test_data, {0x13, 0x3f, 0x17, 0x06, 0x26, 0x3f, 0x35});

} // namespace eul::crc

