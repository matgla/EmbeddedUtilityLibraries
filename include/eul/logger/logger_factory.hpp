#pragma once

#include "eul/logger/logger.hpp"
#include "eul/logger/logger_policy.hpp"
#include "eul/logger/logger_traits.hpp"

namespace eul
{
namespace logger
{

template <typename TimeType, typename LoggingPolicy, Writable... Streams>
class LoggerFactory
{
public:
    using LoggerType = Logger<LoggingPolicy, TimeType, Streams...>;

    LoggerFactory(const TimeType& time)
        : time_(time)
    {
    }

    constexpr auto create(const std::string_view& name) const
    {
        return LoggerType(name, time_);
    }


protected:
    const TimeType& time_;
};

} // namespace logger
} // namespace eul
