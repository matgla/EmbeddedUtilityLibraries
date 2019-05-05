#pragma once

#include <string_view>

#include "eul/container/observable/observing_node.hpp"

namespace eul
{
namespace logger
{

class logger_stream
{
public:
    using observing_node_type = eul::container::observing_node<logger_stream*>;
    logger_stream();
    virtual ~logger_stream() = default;

    virtual void write(const std::string_view& str) = 0;
    observing_node_type& observing_node();


private:
    observing_node_type observing_node_;
};

} // namespace logger
} // namespace eul
