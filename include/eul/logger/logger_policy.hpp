#pragma once

namespace eul
{
namespace logger
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


} // namespace logger
} // namespace eul
