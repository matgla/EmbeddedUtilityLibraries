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

#include <eul/crc/crc5.hpp>

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

static_assert(std::is_same_v<Crc5_EPC, Crc5_EPC_C1G2>, "Crc5_EPC should be same as Crc5_EPC_C1G2");
static_assert(std::is_same_v<Crc5_G_704, Crc5_ITU>, "Crc5_G_704 should be same as Crc5_ITU");
        
REGISTER_CRC_TEST(Crc5_EPC,  test_data, {0x00, 0x15, 0x06, 0x05, 0x07, 0x17, 0x1b});
REGISTER_CRC_TEST(Crc5_ITU,  test_data, {0x07, 0x00, 0x1b, 0x11, 0x0b, 0x00, 0x0a});
REGISTER_CRC_TEST(Crc5_USB,  test_data, {0x19, 0x01, 0x04, 0x06, 0x09, 0x0f, 0x10});

} // namespace eul::crc

