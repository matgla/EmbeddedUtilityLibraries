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

namespace eul::logger
{

struct DisabledPolicy
{
    constexpr static bool debug_enabled   = false;
    constexpr static bool info_enabled    = false;
    constexpr static bool error_enabled   = false;
    constexpr static bool warning_enabled = false;
    constexpr static bool trace_enabled   = false;
};

struct ErrorPolicy
{
    constexpr static bool debug_enabled   = false;
    constexpr static bool info_enabled    = false;
    constexpr static bool error_enabled   = true;
    constexpr static bool warning_enabled = false;
    constexpr static bool trace_enabled   = false;
};

struct WarningPolicy
{
    constexpr static bool debug_enabled   = false;
    constexpr static bool info_enabled    = false;
    constexpr static bool error_enabled   = true;
    constexpr static bool warning_enabled = true;
    constexpr static bool trace_enabled   = false;
};

struct InfoPolicy
{
    constexpr static bool debug_enabled   = false;
    constexpr static bool info_enabled    = true;
    constexpr static bool error_enabled   = true;
    constexpr static bool warning_enabled = true;
    constexpr static bool trace_enabled   = false;
};

struct DebugPolicy
{
    constexpr static bool debug_enabled   = true;
    constexpr static bool info_enabled    = true;
    constexpr static bool error_enabled   = true;
    constexpr static bool warning_enabled = true;
    constexpr static bool trace_enabled   = false;
};

struct TracePolicy
{
    constexpr static bool debug_enabled   = true;
    constexpr static bool info_enabled    = true;
    constexpr static bool error_enabled   = true;
    constexpr static bool warning_enabled = true;
    constexpr static bool trace_enabled   = true;
};

#ifdef LOG_LEVEL_TRACE
using CurrentLoggingPolicy = TracePolicy;
#elif LOG_LEVEL_DEBUG
using CurrentLoggingPolicy = DebugPolicy;
#elif LOG_LEVEL_INFO
using CurrentLoggingPolicy = InfoPolicy;
#elif LOG_LEVEL_WARNING
using CurrentLoggingPolicy = WarningPolicy;
#elif LOG_LEVEL_ERROR
using CurrentLoggingPolicy = ErrorPolicy;
#else
using CurrentLoggingPolicy = DisabledPolicy;
#endif // LOG_LEVEL_TRACE


} // namespace eul::logger
