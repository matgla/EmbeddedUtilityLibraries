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

#include <eul/crc/crc16.hpp>

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
        
static_assert(std::is_same_v<Crc16_XMODEM, Crc16_CCITT_ZERO>, "Crc16_CCIT_ZERO should be same as Crc16_XMODEM");
static_assert(std::is_same_v<Crc16, Crc16_ARC>, "Crc16 should be same as Crc16_ARC");
static_assert(std::is_same_v<Crc16, Crc16_LHA>, "Crc16 should be same as Crc16_LHA");
static_assert(std::is_same_v<Crc16, Crc16_IBM>, "Crc16 should be same as Crc16_IBM");
static_assert(std::is_same_v<Crc16_DARC, Crc16_GENIBUS>, "Crc16_DARC should be same as Crc16_GENIBUS");
static_assert(std::is_same_v<Crc16_EPC, Crc16_GENIBUS>, "Crc16_EPC should be same as Crc16_GENIBUS");
static_assert(std::is_same_v<Crc16_EPC_C1G2, Crc16_GENIBUS>, "Crc16_EPC_C1G2 should be same as Crc16_GENIBUS");
static_assert(std::is_same_v<Crc16_ICODE, Crc16_GENIBUS>, "Crc16_ICODE should be same as Crc16_GENIBUS");
static_assert(std::is_same_v<Crc16_AUTOSAR, Crc16_CCIT_FALSE>, "Crc16_AUTOSAR should be same as Crc16_CCIT_FALSE");
static_assert(std::is_same_v<Crc16_IBM_3740, Crc16_CCIT_FALSE>, "Crc16_IBM_3740 should be same as Crc16_CCIT_FALSE");
static_assert(std::is_same_v<Crc16_IBM_SDLC, Crc16_X_25>, "Crc16_IBM_3740 should be same as Crc16_X_25");
static_assert(std::is_same_v<Crc16_ISO_HDLC, Crc16_X_25>, "Crc16_ISO_HDLC should be same as Crc16_X_25");
static_assert(std::is_same_v<Crc16_ISO_IEC_14443_3_B, Crc16_X_25>, "Crc16_ISO_IEC_14443_3_B should be same as Crc16_X_25");
static_assert(std::is_same_v<Crc16_B, Crc16_X_25>, "Crc16_B should be same as Crc16_X_25");
static_assert(std::is_same_v<Crc16_A, Crc16_ISO_IEC_14443_3_A>, "Crc16_A should be same as Crc16_ISO_IEC_14443_3_A");
static_assert(std::is_same_v<Crc16_CCITT, Crc16_KERMIT>, "Crc16_CCITT should be same as Crc16_KERMIT");
static_assert(std::is_same_v<Crc16_CCITT_TRUE, Crc16_KERMIT>, "Crc16_CCITT_TRUE should be same as Crc16_KERMIT");
static_assert(std::is_same_v<Crc16_V_41_LSB, Crc16_KERMIT>, "Crc16_V_41_LSB should be same as Crc16_KERMIT");
static_assert(std::is_same_v<Crc16_MAXIM_DOW, Crc16_MAXIM>, "Crc16_MAXIM_DOW should be same as Crc16_MAXIM");
static_assert(std::is_same_v<Crc16_IEC_61158_2, Crc16_PROFIBUS>, "Crc16_IEC_61158_2 should be same as Crc16_PROFIBUS");
static_assert(std::is_same_v<Crc16_AUG_CCIT, Crc16_SPI_FUJITSU>, "Crc16_AUG_CCIT should be same as Crc16_SPI_FUJITSU");
static_assert(std::is_same_v<Crc16_UMTS, Crc16_BUYPASS>, "Crc16_UMTS should be same as Crc16_BUYPASS");
static_assert(std::is_same_v<Crc16_VERIFONE, Crc16_BUYPASS>, "Crc16_VERIFONE should be same as Crc16_BUYPASS");
static_assert(std::is_same_v<Crc16_ACORN, Crc16_XMODEM>, "Crc16_ACORN should be same as Crc16_XMODEM");
static_assert(std::is_same_v<Crc16_LTE, Crc16_XMODEM>, "Crc16_LTE should be same as Crc16_XMODEM");
static_assert(std::is_same_v<Crc16_V_41_MSB, Crc16_XMODEM>, "Crc16_V_41_MSB should be same as Crc16_XMODEM");
static_assert(std::is_same_v<Crc16_CCITT_ZERO, Crc16_XMODEM>, "Crc16_CCITT_ZERO should be same as Crc16_XMODEM");

REGISTER_CRC_TEST(Crc16_CCITT_ZERO,    test_data,  {0x31c3, 0x0000, 0x1ef0, 0x1231, 0xfefb, 0x0000, 0x99cf});
REGISTER_CRC_TEST(Crc16_ARC,           test_data,  {0xbb3d, 0x0000, 0x4040, 0xcc01, 0x781d, 0x0000, 0x9401});
REGISTER_CRC_TEST(Crc16_AUG_CCIT,      test_data,  {0xe5cc, 0xcc9c, 0xD26C, 0xdead, 0x0f35, 0x84c0, 0x97df});
REGISTER_CRC_TEST(Crc16_BUYPASS,       test_data,  {0xfee8, 0x0000, 0x0202, 0x8063, 0x1881, 0x0000, 0x8029});
REGISTER_CRC_TEST(Crc16_CCIT_FALSE,    test_data,  {0x29b1, 0xe1f0, 0xff00, 0xf3c1, 0xeff7, 0x1d0f, 0x1d0f});
REGISTER_CRC_TEST(Crc16_CDMA2000,      test_data,  {0x4c06, 0x6b6c, 0xff00, 0xf68d, 0x8258, 0x8a85, 0x8a85});
REGISTER_CRC_TEST(Crc16_DDS_110,       test_data,  {0x9ecf, 0x8e03, 0x8c01, 0x0e60, 0xc081, 0x0024, 0x80f1});
REGISTER_CRC_TEST(Crc16_DECT_R,        test_data,  {0x007e, 0x0001, 0x751d, 0x5891, 0xfd65, 0x0001, 0x983c});
REGISTER_CRC_TEST(Crc16_DECT_X,        test_data,  {0x007f, 0x0000, 0x751c, 0x5890, 0xfd64, 0x0000, 0x983d});
REGISTER_CRC_TEST(Crc16_DNP,           test_data,  {0xea82, 0xffff, 0xedca, 0x4d94, 0x02dc, 0xffff, 0x7a8f});
REGISTER_CRC_TEST(Crc16_EN_13757,      test_data,  {0xc2b7, 0xffff, 0x53b7, 0x6e00, 0xe5fb, 0xffff, 0xf15e});
REGISTER_CRC_TEST(Crc16_GENIBUS,       test_data,  {0xd64e, 0x1e0f, 0x00ff, 0x0c3e, 0x1008, 0xe2f0, 0xe2f0});
REGISTER_CRC_TEST(Crc16_MAXIM,         test_data,  {0x44c2, 0xffff, 0xbfbf, 0x33fe, 0x87e2, 0xffff, 0x6bfe});
REGISTER_CRC_TEST(Crc16_MCRF4XX,       test_data,  {0x6f91, 0x0f87, 0x00ff, 0x1f06, 0x4097, 0xf0b8, 0xf0b8});
REGISTER_CRC_TEST(Crc16_RIELLO,        test_data,  {0x63d0, 0x99b4, 0x96cc, 0x8935, 0x7608, 0xf336, 0xd4ff});
REGISTER_CRC_TEST(Crc16_T10_DIF,       test_data,  {0xd0db, 0x0000, 0x55b3, 0x54cd, 0x3df7, 0x0000, 0x77b5});
REGISTER_CRC_TEST(Crc16_TELEDISK,      test_data,  {0x0fb3, 0x0000, 0xf087, 0x2f03, 0x98f1, 0x0000, 0x30b8});
REGISTER_CRC_TEST(Crc16_TMS37157,      test_data,  {0x26b1, 0x8537, 0x8a4f, 0x95b6, 0x5e9d, 0x45b9, 0x0b46});
REGISTER_CRC_TEST(Crc16_USB,           test_data,  {0xb4c8, 0xbf40, 0xff00, 0x7341, 0x87c6, 0x4ffe, 0x4ffe});
REGISTER_CRC_TEST(Crc16_A,             test_data,  {0xbf05, 0x51fe, 0x5e86, 0x417f, 0x7049, 0x1ea0, 0xa599});
REGISTER_CRC_TEST(Crc16_KERMIT,        test_data,  {0x2189, 0x0000, 0x0f78, 0x1081, 0x701f, 0x0000, 0xf399});
REGISTER_CRC_TEST(Crc16_MODBUS,        test_data,  {0x4b37, 0x40bf, 0x00ff, 0x8cbe, 0x7839, 0xb001, 0xb001});
REGISTER_CRC_TEST(Crc16_X_25,          test_data,  {0x906e, 0xf078, 0xff00, 0xe0f9, 0xbf68, 0x0f47, 0x0f47});
REGISTER_CRC_TEST(Crc16_CMS,           test_data,  {0xaee7});
REGISTER_CRC_TEST(Crc16_GSM,           test_data,  {0xce3c});
REGISTER_CRC_TEST(Crc16_LJ1200,        test_data,  {0xbdf4});
REGISTER_CRC_TEST(Crc16_M17,           test_data,  {0x772b});
REGISTER_CRC_TEST(Crc16_NRSC_5,        test_data,  {0xa066});
REGISTER_CRC_TEST(Crc16_OPENSAFETY_A,  test_data,  {0x5d38});
REGISTER_CRC_TEST(Crc16_OPENSAFETY_B,  test_data,  {0x20fe});
REGISTER_CRC_TEST(Crc16_PROFIBUS,      test_data,  {0xa819});

} // namespace eul::crc

