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

#include <eul/crc/crc64.hpp>

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

static_assert(std::is_same_v<Crc64_ECMA_182, Crc64>, "Crc64_ECMA_182 should be same as Crc64");

        
REGISTER_CRC_TEST(Crc64_ECMA_182, test_data,  {0x6c40df5f0b497347, 0x0000000000000000, 0x9afce626ce85b507, 0x663d78ff90e185ef, 0xadbce7f22506acb7, 0x0000000000000000, 0xd2f9d878539e5ad0});
REGISTER_CRC_TEST(Crc64_GO_ISO,   test_data,  {0xb90956c775a41001, 0x6f90000000000000, 0xff00000000000000, 0x7490000000000000, 0xe4d1eead2cf00000, 0x6fff900000000000, 0xffffffff00000000});
REGISTER_CRC_TEST(Crc64_WE,       test_data,  {0x62ec59e3f1a4f00a, 0x9afce626ce85b5f8, 0x00000000000000ff, 0xfcc19ed95e643017, 0x01bb2585de4d8b64, 0xe15a528ae9b20842, 0x00000000ffffffff});
REGISTER_CRC_TEST(Crc64_XZ,       test_data,  {0x995dc9bbdf1939fa, 0x1fada17364673f59, 0xff00000000000000, 0x6236004b35545910, 0xaca26639776c08de, 0x42104d97514a5a87, 0xffffffff00000000});
REGISTER_CRC_TEST(Crc64_MS,       test_data,  {0x75d4b74f024eceea});

} // namespace eul::crc

