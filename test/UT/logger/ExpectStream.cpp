#include "ExpectStream.hpp"

#include <ctime>
#include <iostream>


namespace eul::logger 
{

void ExpectStream::write(const std::string_view& str) 
{
    std::string tmp{str};
    if (expect_.empty())
    {
        std::cerr << "Unexpected print: " << str << std::endl;
        FAIL();
    }
    
    if(tmp.ends_with("\n"))
    {
        got_ << tmp; 
        REQUIRE(got_.str() == expect_);
        got_.clear();
        return;
    }
    got_ << tmp;
}

void ExpectStream::expect(const std::string& message, const std::chrono::milliseconds& milliseconds)
{
    std::time_t time = milliseconds.count();
    struct tm time_tm{}; 
    #if defined(_MSC_VER)
        localtime_s(&time_tm, &time);
    #else 
        localtime_r(&time, &time_tm);
    #endif
    char formatted_time[26];
    #if defined(_MSC_VER)
        ctime_s(formatted_time, sizeof formatted_time, &time);
    #else 
        ctime_r(&time, formatted_time);
    #endif 
    formatted_time[24] = 0;
    std::stringstream str;
    str << "<" << formatted_time << "> " << message;
    expect_ = str.str();
}

void ExpectStream::expect_none()
{
    expect_ = "";
}

} // eul::logger 
