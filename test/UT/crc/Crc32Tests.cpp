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

#include <eul/crc/crc32.hpp>

namespace eul::crc
{

const static std::vector<std::vector<uint8_t>> test_data{
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39},
    {0x00},
    {0xff},
    {0x10},
    {0x2, 0x3, 0xab, 0xcd, 0xef},
    {0x00, 0x00},
    {0xff, 0xff, 0xff, 0xff}
};
        
static_assert(std::is_same_v<Crc32_AXIM, Crc32_Q>, "Crc32_AXIM should be same as Crc32_Q");
static_assert(std::is_same_v<Crc32_BASE91_D, Crc32_D>, "Crc32_BASE91_D should be same as Crc32_D");
static_assert(std::is_same_v<Crc32_DECT_B, Crc32_BZIP>, "Crc32_DECT_B should be same as Crc32_BZIP");
static_assert(std::is_same_v<Crc32_AAL5, Crc32_BZIP>, "Crc32_AAL5 should be same as Crc32_BZIP");
static_assert(std::is_same_v<Crc32_CKSUM, Crc32_POSIX>, "Crc32_CKSUM should be same as Crc32_POSIX");
static_assert(std::is_same_v<Crc32_BASE91_C, Crc32_C>, "Crc32_BASE91_C should be same as Crc32_C");
static_assert(std::is_same_v<Crc32_CASTAGNOLI, Crc32_C>, "Crc32_CASTAGNOLI should be same as Crc32_C");
static_assert(std::is_same_v<Crc32_INTERLAKEN, Crc32_C>, "Crc32_INTERLAKEN should be same as Crc32_C");
static_assert(std::is_same_v<Crc32_ADCCP, Crc32>, "Crc32_ADCCP should be same as Crc32");
static_assert(std::is_same_v<Crc32_ISO_HDLC, Crc32>, "Crc32_ISO_HDLC should be same as Crc32");
static_assert(std::is_same_v<Crc32_V42, Crc32>, "Crc32_V42 should be same as Crc32");
static_assert(std::is_same_v<Crc32_XZ, Crc32>, "Crc32_XZ should be same as Crc32");

REGISTER_CRC_TEST(Crc32,              test_data,  {0xcbf43926, 0xd202ef8d, 0xff000000, 0xcfb5ffe9, 0x359beff8, 0x41d912ff, 0xffffffff});
REGISTER_CRC_TEST(Crc32_BZIP,         test_data,  {0xfc891918, 0xb1f7404b, 0x000000ff, 0xfde69b3b, 0xb234f7f1, 0xff489b82, 0xffffffff});
REGISTER_CRC_TEST(Crc32_C,            test_data,  {0xe3069283, 0x527d5351, 0xff000000, 0x4223943e, 0x96a5c065, 0xf16177d2, 0xffffffff});
REGISTER_CRC_TEST(Crc32_D,            test_data,  {0x87315576, 0x7e5a3823, 0xff000000, 0x3bd394ae, 0xbcf7c10c, 0x89514bd0, 0xffffffff});
REGISTER_CRC_TEST(Crc32_MPEG2,        test_data,  {0x0376e6e7, 0x4e08bfb4, 0xffffff00, 0x021964c4, 0x4dcb080e, 0x00b7647d, 0x00000000});
REGISTER_CRC_TEST(Crc32_POSIX,        test_data,  {0x765e7680, 0xffffffff, 0x4e08bf4b, 0xb3ee248f, 0xf5244c6d, 0xffffffff, 0x38fb2284});
REGISTER_CRC_TEST(Crc32_Q,            test_data,  {0x3010bf7f, 0x00000000, 0x80006eee, 0x98d8d3b9, 0xef552553, 0x00000000, 0x90a54352});
REGISTER_CRC_TEST(Crc32_JAMCRC,       test_data,  {0x340bc6d9, 0x2dfd1072, 0x00ffffff, 0x304a0016, 0xca641007, 0xbe26ed00, 0x00000000});
REGISTER_CRC_TEST(Crc32_XFER,         test_data,  {0xbd0be338, 0x00000000, 0x00006565, 0x00000af0, 0xb792cc90, 0x00000000, 0x00003c56});
REGISTER_CRC_TEST(Crc32_AUTOSAR,      test_data,  {0x1697d06a});
REGISTER_CRC_TEST(Crc32_CD_ROM_EDC,   test_data,  {0x6ec2edc4});
REGISTER_CRC_TEST(Crc32_MEF,          test_data,  {0xd2c22f51});

} // namespace eul::crc

