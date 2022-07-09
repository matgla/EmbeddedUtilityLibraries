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

#include <eul/crc/crc8.hpp>

namespace eul::crc
{

const static std::vector<std::vector<uint8_t>> test_data{
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39},
    {0x2, 0x3, 0xff},
    {0x2, 0xff, 0xff},
    {0x00, 0x00},
    {0xff, 0xff, 0xff, 0xff},
    {0x00},
    {0xff},
};
        
static_assert(std::is_same_v<Crc8_SAE_J1850_ZERO, Crc8_GSM_A>, "Crc8_SAE_J1850_ZERO should be same as Crc8_GSM_A");
static_assert(std::is_same_v<Crc8_AUTOSAR, Crc8_8H2F>, "Crc8_SAE_J1850_ZERO should be same as Crc8_GSM_A");
static_assert(std::is_same_v<Crc8_TECH_3250, Crc8_EBU>, "Crc8_TECH_3250 should be same as Crc8_EBU");
static_assert(std::is_same_v<Crc8_AES, Crc8_EBU>, "Crc8_AES should be same as Crc8_EBU");
static_assert(std::is_same_v<Crc8_I_432_1, Crc8_ITU>, "Crc8_I_432_1 should be same as Crc8_EBU");
static_assert(std::is_same_v<Crc8_MAXIM_DOW, Crc8_MAXIM>, "Crc8_MAXIM_DOW should be same as Crc8_MAXIM");
static_assert(std::is_same_v<Crc8_DOW, Crc8_MAXIM>, "Crc8_DOW should be same as Crc8_MAXIM");
static_assert(std::is_same_v<Crc8_SMBUS, Crc8>, "Crc8_SMBUS should be same as Crc8");

REGISTER_CRC_TEST(Crc8,                test_data,  {0xf4, 0x1a, 0xf2, 0x00, 0xde, 0x00, 0xf3});
REGISTER_CRC_TEST(Crc8_SAE_J1850,      test_data,  {0x4b, 0xe2, 0x77, 0xbe, 0x74, 0x3b, 0xff});
REGISTER_CRC_TEST(Crc8_SAE_J1850_ZERO, test_data,  {0x37, 0x13, 0x86, 0x00, 0x2d, 0x00, 0xc4});
REGISTER_CRC_TEST(Crc8_8H2F,           test_data,  {0xdf, 0xdc, 0x70, 0x47, 0x6c, 0xbd, 0xff});
REGISTER_CRC_TEST(Crc8_CDMA2000,       test_data,  {0xda, 0x3b, 0xb0, 0xb1, 0x0c, 0x7b, 0x00});
REGISTER_CRC_TEST(Crc8_DARC,           test_data,  {0x15, 0x31, 0xf0, 0x00, 0x03, 0x00, 0xc6});
REGISTER_CRC_TEST(Crc8_DVB_S2,         test_data,  {0xbc, 0x37, 0x52, 0x00, 0x21, 0x00, 0xf9});
REGISTER_CRC_TEST(Crc8_EBU,            test_data,  {0x97, 0x91, 0xd7, 0x82, 0xd1, 0x23, 0x00});
REGISTER_CRC_TEST(Crc8_ICODE,          test_data,  {0x7e, 0x1e, 0x8b, 0xd9, 0xac, 0xfe, 0x3a});
REGISTER_CRC_TEST(Crc8_ITU,            test_data,  {0xa1, 0x4f, 0xa7, 0x55, 0x8b, 0x55, 0xa6});
REGISTER_CRC_TEST(Crc8_MAXIM,          test_data,  {0xa1, 0x2f, 0xfb, 0x00, 0x8d, 0x00, 0x35});
REGISTER_CRC_TEST(Crc8_ROHC,           test_data,  {0xd0, 0xcd, 0x91, 0xeb, 0xf0, 0xcf, 0x00});
REGISTER_CRC_TEST(Crc8_WCDMA,          test_data,  {0x25, 0xd3, 0xf1, 0x00, 0xc5, 0x00, 0xde});
REGISTER_CRC_TEST(Crc8_GSM_B,          test_data,  {0x94});
REGISTER_CRC_TEST(Crc8_BLUETOOTH,      test_data,  {0x26});
REGISTER_CRC_TEST(Crc8_HITAG,          test_data,  {0xb4});
REGISTER_CRC_TEST(Crc8_LTE,            test_data,  {0xea});
REGISTER_CRC_TEST(Crc8_MIFARE_MAD,     test_data,  {0x99});
REGISTER_CRC_TEST(Crc8_NRSC_5,         test_data,  {0xf7});
REGISTER_CRC_TEST(Crc8_OPENSAFETY,     test_data,  {0x3e});

} // namespace eul::crc

