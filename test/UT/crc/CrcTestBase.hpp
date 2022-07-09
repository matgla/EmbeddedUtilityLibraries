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

#include <span>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

namespace eul::crc
{

using TestInputType = std::vector<std::vector<uint8_t>>; 
using ResultType = std::vector<uint64_t>;

struct TestData
{
    const char* name;
    const TestInputType& input;
    ResultType results; 
};

template <typename CrcType>
class CrcShould : public ::testing::Test
{
protected:
<<<<<<< HEAD
    std::string print_testcase(std::span<const uint8_t> bytes);
=======
    std::string print_testcase(std::span<const uint8_t> data);
>>>>>>> 2942017e797c86fbe4d2e37deb4f20f0c18dc9cf

    const static TestData data;
};


TYPED_TEST_SUITE_P(CrcShould);

template <typename CrcType>
<<<<<<< HEAD
std::string CrcShould<CrcType>::print_testcase(std::span<const uint8_t> bytes)
{
    std::stringstream str;
    str << "Used algorithm: " << this->data.name << " for data: " << std::hex << "{";
    for (std::size_t i = 0; i < bytes.size() - 1; ++i)
    {
        str << "0x" << +bytes[i] << ", ";
    }
    str << "0x" << +bytes[bytes.size() - 1] << "}";
=======
std::string CrcShould<CrcType>::print_testcase(std::span<const uint8_t> data)
{
    std::stringstream str;
    str << "Used algorithm: " << this->data.name << " for data: " << std::hex << "{";
    for (std::size_t i = 0; i < data.size() - 1; ++i)
    {
        str << "0x" << +data[i] << ", ";
    }
    str << "0x" << +data[data.size() - 1] << "}";
>>>>>>> 2942017e797c86fbe4d2e37deb4f20f0c18dc9cf
    return str.str();
}

TYPED_TEST_P(CrcShould, Calculate) 
{
    for (std::size_t i = 0; i < this->data.results.size(); ++i)
    {
        ASSERT_TRUE(i < this->data.input.size());
        const auto& input = this->data.input[i];
        EXPECT_EQ(TypeParam::calculate(input), this->data.results[i]) << this->print_testcase(input);
    }
}

REGISTER_TYPED_TEST_SUITE_P(CrcShould, Calculate);


#define REGISTER_CRC_TEST(algorithm, input, ...) \
    template<> const TestData CrcShould<algorithm>::data{ \
        #algorithm, input , __VA_ARGS__ \
    }; \
    INSTANTIATE_TYPED_TEST_SUITE_P(algorithm, CrcShould, algorithm);


} // namespace eul::crc

