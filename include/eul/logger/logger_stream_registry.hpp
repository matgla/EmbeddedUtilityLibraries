#pragma once

#include "eul/container/observable/observing_list.hpp"

#include "eul/logger/logger_stream.hpp"
#include "eul/logger/logger_stream_registry.hpp"

namespace eul
{
namespace logger
{

class logger_stream_registry
{
public:
    using  stream_node = eul::container::observing_node<logger_stream*>;
    using streams = eul::container::observing_list<stream_node>;
    static logger_stream_registry& get();
    void register_stream(logger_stream& stream);

    streams& get_streams() const;


private:
    logger_stream_registry() = default;

    streams streams_;
};

} // namespace logger
} // namespace eul
