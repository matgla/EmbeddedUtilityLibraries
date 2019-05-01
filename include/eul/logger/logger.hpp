#pragma once

#include <string_view>

#include "eul/container/observable/observing_list.hpp"
#include "eul/logger/logger_stream_registry.hpp"
#include "eul/logger/logger_traits.hpp"
#include "eul/time/ITimeProvider.hpp"
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

class LoggerPrinter final
{
public:
    LoggerPrinter(
        const std::string_view& prefix,
        const std::string_view& name,
        const time::ITimeProvider& time)
        : prefix_(prefix)
        , name_(name)
        , time_(time)
    {
    }

    ~LoggerPrinter()
    {
        write_to_streams("\n");
    }

    const LoggerPrinter& operator<<(const std::string_view& str) const
    {
        write_to_streams(str);
        return *this;
    }

    template<typename T>
    const LoggerPrinter& operator<<(const gsl::span<T>& data) const
    {
        write_to_streams(data);
        return *this;
    }

    const LoggerPrinter& operator<<(int data) const
    {
        char number[21];
        utils::itoa(data, number);
        write_to_streams(number);
        return *this;
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

    void write_to_streams(const std::string_view& data) const
    {
        for (auto& stream : logger_stream_registry::get().get_streams())
        {
            stream.data()->write(data);
        }
    }

    const std::string_view prefix_;
    const std::string_view name_;
    const time::ITimeProvider& time_;
};

class Logger
{
public:
    Logger(const std::string_view& name, const time::ITimeProvider& time)
        : name_(name)
        , time_(time)
    {
    }

    Logger(const Logger&) = default;
    Logger(Logger&&)      = default;
    ~Logger() = default;

    Logger& operator=(const Logger&& other) = delete;
    Logger& operator=(const Logger& other) = delete;

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        return LoggerPrinter("DBG", name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        return LoggerPrinter("INF", name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        return LoggerPrinter("WRN", name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        return LoggerPrinter("ERR", name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        return SuppressingLogger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        printHeader("TRC");
        return LoggerPrinter(name_, time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        return SuppressingLogger();
    }

protected:

    const std::string_view name_;
    const time::ITimeProvider& time_;
};

} // namespace logger
} // namespace eul
