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

#include <eul/crc/crc30.hpp>

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

REGISTER_CRC_TEST(Crc30_CDMA, test_data, {0x04c34abf, 0x1faf6629, 0x000000ff, 0x1d213461, 0x13edd117, 0x3f2e4585, 0x3f9e8c71});

} // namespace eul::crc

