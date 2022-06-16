// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
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

#pragma once

#include <optional>
#include <string_view>

#include "eul/container/observable/observing_list.hpp"
#include "eul/logger/logger_policy.hpp"
#include "eul/logger/logger_printer.hpp"
#include "eul/logger/logger_stream_registry.hpp"
#include "eul/logger/suppressing_logger.hpp"
#include "eul/time/i_time_provider.hpp"

namespace eul::logger
{

class logger
{
public:
    logger(const std::string_view& name, const time::i_time_provider& time)
        : name_(name)
        , time_(&time)
    {
    }

    logger(const std::string_view& name, const std::string_view& prefix, const time::i_time_provider& time)
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

    void set_time_provider(const time::i_time_provider& time)
    {
        time_ = &time;
    }

    template <typename T>
    T debug() const
    {
        if constexpr (!CurrentLoggingPolicy::debug_enabled)
        {
            return suppressing_logger();
        }

        if (prefix_ && prefix_ != "")
        {
            return logger_printer("DBG", name_, *prefix_, *time_);
        }
        return logger_printer("DBG", name_, *time_);
    }

    template <typename T>
    T info() const
    {
        if constexpr (!CurrentLoggingPolicy::info_enabled)
        {
            return suppressing_logger();
        }

        if (prefix_ && prefix_ != "")
        {
            return logger_printer("INF", name_, *prefix_, *time_);
        }
        return logger_printer("INF", name_, *time_);
    }

    template <typename T>
    T warning() const
    {
        if constexpr (!CurrentLoggingPolicy::warning_enabled)
        {
            return suppressing_logger();
        }

        if (prefix_ && prefix_ != "")
        {
            return logger_printer("WRN", name_, *prefix_, *time_);
        }
        return logger_printer("WRN", name_, *time_);
    }

    template <typename T>
    T error() const
    {
        if constexpr (!CurrentLoggingPolicy::error_enabled)
        {
            return suppressing_logger();
        }

        if (prefix_ && prefix_ != "")
        {
            return logger_printer("ERR", name_, *prefix_, *time_);
        }
        return logger_printer("ERR", name_, *time_);
    }

    template <typename T>
    T trace() const
    {
        if constexpr (!CurrentLoggingPolicy::trace_enabled)
        {
            return suppressing_logger();
        }

        if (prefix_ && prefix_ != "")
        {
            return logger_printer("TRC", name_, *prefix_, *time_);
        }
        return logger_printer("TRC", name_, *time_);
    }

private:
    const std::string_view name_;
    const std::optional<std::string_view> prefix_;
    const time::i_time_provider* time_;
};

} // namespace eul::logger
