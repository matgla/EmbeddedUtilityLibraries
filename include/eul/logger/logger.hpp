#pragma once

#include <string_view>

#include "eul/container/observable/observing_list.hpp"
#include "eul/logger/logger_stream_registry.hpp"
#include "eul/logger/logger_policy.hpp"
#include "eul/logger/suppressing_logger.hpp"
#include "eul/logger/logger_printer.hpp"
#include "eul/time/i_time_provider.hpp"

namespace eul
{
namespace logger
{

class logger
{
public:
    logger(const std::string_view& name, time::i_time_provider& time)
        : name_(name)
        , time_(&time)
    {
    }

    logger(const logger&) = default;
    logger(logger&&)      = default;
    ~logger() = default;

    logger& operator=(const logger&& other) = delete;
    logger& operator=(const logger& other) = delete;

    void set_time_provider(time::i_time_provider& time)
    {
        time_ = &time;
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        return logger_printer("DBG", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::debug_enabled, Dummy> = 0>
    auto debug() const
    {
        return suppressing_logger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        return logger_printer("INF", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::info_enabled, Dummy> = 0>
    auto info() const
    {
        return suppressing_logger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        return logger_printer("WRN", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::warning_enabled, Dummy> = 0>
    auto warning() const
    {
        return suppressing_logger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        return logger_printer("ERR", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::error_enabled, Dummy> = 0>
    auto error() const
    {
        return suppressing_logger();
    }

    template <typename Dummy = char, typename std::enable_if_t<CurrentLoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        return logger_printer("TRC", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        return suppressing_logger();
    }

protected:

    const std::string_view name_;
    time::i_time_provider* time_;
};

} // namespace logger
} // namespace eul
