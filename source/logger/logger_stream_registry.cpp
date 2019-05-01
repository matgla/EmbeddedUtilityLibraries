#include "eul/logger/logger_stream_registry.hpp"

namespace eul
{
namespace logger
{

logger_stream_registry& logger_stream_registry::get()
{
    static logger_stream_registry lsr;
    return lsr;
}

void logger_stream_registry& logger_stream_registry::register_stream(logger_stream& stream)
{
    streams_.push_back(stream.observing_node());
}

logger_stream_registry::streams& logger_stream_registry::get_streams() const
{
    return streams_;
}

} // namespace logger
} // namespace eul
