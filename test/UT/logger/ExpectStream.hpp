#pragma once 

#include <string>
#include <string_view>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include <eul/logger/logger_stream.hpp>

namespace eul::logger 
{

class ExpectStream : public logger_stream 
{
public: 
    void write(const std::string_view& str) override;
    void expect(const std::string& message, const std::chrono::milliseconds& milliseconds);
    void expect_none();

private: 
    std::string expect_;
    std::stringstream got_;
};

} // eul::logger 
