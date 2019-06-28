#pragma once

#include <string_view>

#include "eul/time/fwd.hpp"
#include "eul/logger/logger.hpp"

namespace eul
{
namespace logger
{

class logger_factory
{
public:
    logger_factory(time::i_time_provider& time_provider);

    logger create(const std::string_view& name) const;
    logger create(const std::string_view& name, const std::string_view& prefix) const;

    time::i_time_provider& get_time_provider();
private:
    time::i_time_provider& time_provider_;
};

} // namespace logger
} // namespace eul
