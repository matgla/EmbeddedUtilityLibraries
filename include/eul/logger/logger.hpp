#pragma once

#include <string_view>

#include "eul/logger/logger_traits.hpp"
#include "eul/utils.hpp"

namespace eul
{
namespace logger
{

class SuppressingLogger
{
public:
    template <typename T>
    const SuppressingLogger& operator<<(const T& str) const
    {
        UNUSED(str);
        return *this;
    }
};


template <Writable Stream, Writable... Rest>
struct write_to_all
{
    constexpr static void write(const auto& data)
    {
        Stream::write(data);
        write_to_all<Rest...>::write(data);
    }
};

template <Writable Stream>
struct write_to_all<Stream>
{
    constexpr static void write(const auto& data)
    {
        Stream::write(data);
    }
};


template <typename LoggingPolicy, typename TimeType, Writable... Streams>
class Logger
{
public:
    using LoggerType = Logger<LoggingPolicy, TimeType, Streams...>;
    Logger(const std::string_view& name, const TimeType& time)
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
        write_to_streams("\n");
    }

    const Logger& operator<<(const std::string_view& str) const
    {
        write_to_streams(str);
        return *this;
    }

    template<typename T>
    const Logger& operator<<(const gsl::span<T>& data) const
    {
        write_to_streams(data);
        return *this;
    }

    const Logger& operator<<(int data) const
    {
        char number[21];
        utils::itoa(data, number);
        write_to_streams(number);
        return *this;
    }

    template <typename Dummy = char, typename std::enable_if_t<LoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        printHeader("DBG");
        return LoggerType(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!LoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<LoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        printHeader("INF");
        return LoggerType(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!LoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<LoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        printHeader("WRN");
        return LoggerType(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!LoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<LoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        printHeader("ERR");
        return LoggerType(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!LoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<LoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        printHeader("TRC");
        return LoggerType(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!LoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        return SuppressingLogger();
    }

protected:
    void printHeader(std::string_view level) const
    {
        write_to_streams("<");
        printTimeAndDate();
        write_to_streams("> ");
        write_to_streams(level);
        write_to_streams("/");
        write_to_streams(name_);
        write_to_streams(": ");
    }

    void printTimeAndDate() const
    {
        constexpr const int BufferSize = 30;
        char buffer[BufferSize];
        std::time_t t          = time_.milliseconds().count();
        struct tm* currentTime = std::localtime(&t);

        utils::formatDateAndTime(buffer, BufferSize, currentTime);
        write_to_streams(buffer);
    }

    void write_to_streams(const auto& data) const
    {
        write_to_all<Streams...>::write(data);
    }

    const std::string_view name_;
    const TimeType time_;
};

} // namespace logger
} // namespace eul
