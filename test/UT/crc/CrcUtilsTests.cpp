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

#include <bitset>
#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include <eul/crc/detail/crc_utils.hpp>

TEST(CrcUtilsShould, CorrectlyDeduceTypes)
{
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<1>::type, uint8_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<8>::type, uint8_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<9>::type, uint16_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<16>::type, uint16_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<17>::type, uint32_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<32>::type, uint32_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<33>::type, uint64_t>));
    EXPECT_TRUE((std::is_same_v<eul::crc::detail::deduce_type_from_size<64>::type, uint64_t>));
}

TEST(CrcUtilsShould, reflect1Bit)
{
    EXPECT_EQ(eul::crc::detail::reflect<1>(0b11100001), 0b00000001);
    EXPECT_EQ(eul::crc::detail::reflect<1>(0b11100000), 0b00000000);
}

TEST(CrcUtilsShould, reflect2Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<2>(0b11100011), 0b00000011);
    EXPECT_EQ(eul::crc::detail::reflect<2>(0b11100001), 0b00000010);
    EXPECT_EQ(eul::crc::detail::reflect<2>(0b11100010), 0b00000001);
    EXPECT_EQ(eul::crc::detail::reflect<2>(0b11100000), 0b00000000);
}

TEST(CrcUtilsShould, reflect3Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<7>(0b11100011), 0b01100011);
    EXPECT_EQ(eul::crc::detail::reflect<7>(0b11100001), 0b01000011);
    EXPECT_EQ(eul::crc::detail::reflect<7>(0b11100010), 0b00100011);
    EXPECT_EQ(eul::crc::detail::reflect<7>(0b11100000), 0b00000011);
}

TEST(CrcUtilsShould, reflect8Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<8>(0b11100011), 0b11000111);
    EXPECT_EQ(eul::crc::detail::reflect<8>(0b11100001), 0b10000111);
    EXPECT_EQ(eul::crc::detail::reflect<8>(0b11100010), 0b01000111);
    EXPECT_EQ(eul::crc::detail::reflect<8>(0b11100000), 0b00000111);
}

TEST(CrcUtilsShould, reflect9Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<9>(0b101100011u), 0b110001101);
    EXPECT_EQ(eul::crc::detail::reflect<9>(0b101100001u), 0b100001101);
    EXPECT_EQ(eul::crc::detail::reflect<9>(0b101100010u), 0b010001101);
    EXPECT_EQ(eul::crc::detail::reflect<9>(0b101100000u), 0b000001101);
}

TEST(CrcUtilsShould, reflect15Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b1001011000111010u), 0b010111000110100);
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b1100000000000000u), 0b000000000000001);
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b1000000000000001u), 0b100000000000000);
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b1001011000101010u), 0b010101000110100);
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b0000011010111010u), 0b010111010110000);
    EXPECT_EQ(eul::crc::detail::reflect<15>(0b0001011000111011u), 0b110111000110100);
}

TEST(CrcUtilsShould, reflect16Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b1001011000111010u), 0b0101110001101001);
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b1100000000000000u), 0b0000000000000011);
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b1000000000000001u), 0b1000000000000001);
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b1001011000101010u), 0b0101010001101001);
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b0000011010111010u), 0b0101110101100000);
    EXPECT_EQ(eul::crc::detail::reflect<16>(0b0001011000111011u), 0b1101110001101000);
}

TEST(CrcUtilsShould, reflect17Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b10000000000000000u), 0b00000000000000001);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b00000000000000001u), 0b10000000000000000);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b11001011000111010u), 0b01011100011010011);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b11000000000000000u), 0b00000000000000011);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b11000000000000001u), 0b10000000000000011);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b10001011000101010u), 0b01010100011010001);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b00000011010111010u), 0b01011101011000000);
    EXPECT_EQ(eul::crc::detail::reflect<17>(0b00001011000111011u), 0b11011100011010000);
}

TEST(CrcUtilsShould, reflect32Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<32>(0b10000000000000000000000000000000u), 0b00000000000000000000000000000001u);
    EXPECT_EQ(eul::crc::detail::reflect<32>(0b10000000000000000000000000000011u), 0b11000000000000000000000000000001u);
    EXPECT_EQ(eul::crc::detail::reflect<32>(0b00000000000000000000000000000011u), 0b11000000000000000000000000000000u);
}

TEST(CrcUtilsShould, reflect33Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<33>(0b100000000000000000000000000000000u), 0b000000000000000000000000000000001u);
    EXPECT_EQ(eul::crc::detail::reflect<33>(0b100000000000000000000000000000011u), 0b110000000000000000000000000000001u);
    EXPECT_EQ(eul::crc::detail::reflect<33>(0b000000000000000000000000000000011u), 0b110000000000000000000000000000000u);
}

TEST(CrcUtilsShould, reflect64Bits)
{
    EXPECT_EQ(eul::crc::detail::reflect<64>(uint64_t(0b1000000000000000000000000000000000000000000000000000000000000000ull))
       , uint64_t(0b0000000000000000000000000000000000000000000000000000000000000001ull));
    EXPECT_EQ(eul::crc::detail::reflect<64>(uint64_t(0b1000000000000000000000000000000000000000000000000000000000000011ull))
       , uint64_t(0b1100000000000000000000000000000000000000000000000000000000000001ull));
    EXPECT_EQ(eul::crc::detail::reflect<64>(uint64_t(0b0100000000000000000000000000000000000000000000000000000000000001ull))
       , uint64_t(0b1000000000000000000000000000000000000000000000000000000000000010ull));
}
