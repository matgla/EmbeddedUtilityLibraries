#include "eul/logger/logger_factory.hpp"

#include "eul/time/i_time_provider.hpp"

namespace eul
{
namespace logger
{

logger_factory::logger_factory(time::i_time_provider& time_provider)
    : time_provider_(time_provider)
{
}

logger logger_factory::create(const std::string_view& name) const
{
    return logger(name, time_provider_);
}

time::i_time_provider& logger_factory::get_time_provider()
{
    return time_provider_;
}


} // namespace logger
} // namespace eul
