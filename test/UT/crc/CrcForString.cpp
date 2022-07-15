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

#include <gtest/gtest.h>

#include <eul/crc/crc32.hpp>
#include <eul/crc/crc8.hpp>

namespace eul::crc
{

TEST(CrcForStringShould, CalculateCorrectly)
{
    const char* test = "123456789";

    EXPECT_EQ(eul::crc::Crc32::calculate(test), 0xcbf43926);
    EXPECT_EQ(eul::crc::Crc8::calculate(test), 0xf4);
}

} // namespace eul::crc

