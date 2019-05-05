#include "eul/logger/logger_stream.hpp"

namespace eul
{
namespace logger
{

logger_stream::logger_stream()
    : observing_node_(this)
{
}

logger_stream::observing_node_type& logger_stream::observing_node()
{
    return observing_node_;
}

} // namespace logger
} // namespace eul
