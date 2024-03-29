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

#include <eul/crc/crc7.hpp>

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

static_assert(std::is_same_v<Crc7_MMC, Crc7>, "Crc7_MMC should be same as Crc7");
        
REGISTER_CRC_TEST(Crc7_MMC,  test_data, {0x75, 0x00, 0x79, 0x3d, 0x3b, 0x00, 0x15});
REGISTER_CRC_TEST(Crc7_ROHC, test_data, {0x53, 0x46, 0x79, 0x07, 0x74, 0x23, 0x07});
REGISTER_CRC_TEST(Crc7_UMTS, test_data, {0x61, 0x00, 0x59, 0x78, 0x76, 0x00, 0x53});

} // namespace eul::crc

