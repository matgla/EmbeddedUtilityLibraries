#pragma once

#include <string_view>

#include "eul/utils.hpp"

namespace eul
{

// clang-format off
template <typename T>
concept bool Writable = requires(T a)
{
    { a.write(std::string_view{}) } -> void;
};
// clang-format on

template <Writable Stream, typename TimeType>
class Logger
{
public:
    Logger(std::string_view name, const TimeType& time)
        : name_(name)
        , time_(time)
    {
    }

    Logger(const Logger&) = default;
    Logger(Logger&&)      = default;
    Logger& operator=(const Logger&& other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger()
    {
        Stream::write("\n");
    }

    Logger& operator<<(const std::string_view& str)
    {
        Stream::write(str);
        return *this;
    }

    Logger& operator<<(int data)
    {
        char number[21];
        utils::itoa(data, number);
        Stream::write(number);
        return *this;
    }

    Logger debug()
    {
        printHeader("DBG");
        return Logger(name_);
    }

    Logger info()
    {
        printHeader("INF");
        return Logger(name_);
    }

    Logger warning()
    {
        printHeader("WRN");
        return Logger(name_);
    }

    Logger error()
    {
        printHeader("ERR");
        return Logger(name_);
    }

protected:
    void printHeader(std::string_view level)
    {
        Stream::write("<");
        printTimeAndDate();
        Stream::write("> ");
        Stream::write(level);
        Stream::write("/");
        Stream::write(name_);
        Stream::write(": ");
    }

    void printTimeAndDate()
    {
        constexpr const int BufferSize = 20;
        char buffer[BufferSize];
        std::time_t t          = time_.milliseconds();
        struct tm* currentTime = std::localtime(&t);

        utils::formatDateAndTime(buffer, BufferSize, currentTime);
        Stream::write(buffer);
    }

    std::string_view name_;
    TimeType time_;
};

} // namespace eul
