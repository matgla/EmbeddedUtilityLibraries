#pragma once

#include <string_view>

namespace eul
{
namespace logger
{

class logger_stream
{
public:
    logger_stream();
    virtual ~logger_stream() = default;

    virtual void write(const std::string_view& str) = 0;

private:

};

} // namespace logger
} // namespace eul
