#pragma once

#include <string_view>
#include <optional>

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

    logger(const std::string_view& name, const std::string_view& prefix, time::i_time_provider& time)
        : name_(name)
        , prefix_(prefix)
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
        if (prefix_ && prefix_ != "")
        {
            return logger_printer("DBG", name_, *prefix_, *time_);
        }
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
        if (prefix_ && prefix_ != "")
        {
            return logger_printer("INF", name_, *prefix_, *time_);
        }
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
        if (prefix_ && prefix_ != "")
        {
            return logger_printer("WRN", name_, *prefix_, *time_);
        }
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
        if (prefix_ && prefix_ != "")
        {
            return logger_printer("ERR", name_, *prefix_, *time_);
        }
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
        if (prefix_ && prefix_ != "")
        {
            return logger_printer("TRC", name_, *prefix_, *time_);
        }
        return logger_printer("TRC", name_, *time_);
    }

    template <typename Dummy = char, typename std::enable_if_t<!CurrentLoggingPolicy::trace_enabled, Dummy> = 0>
    auto trace() const
    {
        return suppressing_logger();
    }

protected:

    const std::string_view name_;
    const std::optional<std::string_view> prefix_;
    time::i_time_provider* time_;
};

} // namespace logger
} // namespace eul
