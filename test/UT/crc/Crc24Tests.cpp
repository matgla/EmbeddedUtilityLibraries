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

#include <eul/crc/crc24.hpp>

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

static_assert(std::is_same_v<Crc24_OPENPGP, Crc24>, "Crc24_OPENPGP should be same as Crc24");

REGISTER_CRC_TEST(Crc24_BLE,        test_data, {0xc25a56, 0xe29d2a, 0x71b16a, 0xff022a, 0xb85aba, 0x38b51d, 0x6a857a});
REGISTER_CRC_TEST(Crc24_FLEXRAY_A,  test_data, {0x7979bd, 0xfe41fa, 0x81d7cb, 0x75f081, 0x20872c, 0x6301fa, 0x3848f3});
REGISTER_CRC_TEST(Crc24_FLEXRAY_B,  test_data, {0x1f23b8, 0x0ebdac, 0x712b9d, 0x850cd7, 0xbeab52, 0x7e18bf, 0x1a021c});
REGISTER_CRC_TEST(Crc24_INTERLAKEN, test_data, {0xb4f3e6, 0xdaf828, 0x0000ff, 0x6ffe31, 0x1141c7, 0xfed93a, 0x250728});
REGISTER_CRC_TEST(Crc24_LTE_A,      test_data, {0xcde703, 0x000000, 0xdd8538, 0x56a868, 0x8363b1, 0x000000, 0xb75584});
REGISTER_CRC_TEST(Crc24_LTE_B,      test_data, {0x23ef52, 0x000000, 0x003e3e, 0x000528, 0x3a001f, 0x000000, 0x8ffc1f});
REGISTER_CRC_TEST(Crc24_OPENPGP,    test_data, {0x21cf02, 0x6169d3, 0xbceceb, 0x37c1bb, 0xa68c93, 0xfaedc0, 0x410c77});
REGISTER_CRC_TEST(Crc24_OS_9,       test_data, {0x200fa5, 0x003ec1, 0x0000ff, 0x003be9, 0x45f003, 0x3effc1, 0xffc1c1});

} // namespace eul::crc

