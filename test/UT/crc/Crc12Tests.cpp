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

#include <eul/crc/crc12.hpp>

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


REGISTER_CRC_TEST(Crc12_CDMA2000, test_data, {0xd4d, 0xacc, 0xf00, 0x10e, 0xff7, 0x9d7, 0x37b});
REGISTER_CRC_TEST(Crc12_DECT,     test_data, {0xf5b, 0x000, 0x606, 0x088, 0x343, 0x000, 0x0f9});
REGISTER_CRC_TEST(Crc12_GSM,      test_data, {0xb34, 0xfff, 0xe70, 0x1a3, 0x5c7, 0xfff, 0x7ee});
REGISTER_CRC_TEST(Crc12_UMTS,     test_data, {0xdaf, 0x000, 0x606, 0x110, 0xc2c, 0x000, 0x9f0});

} // namespace eul::crc

