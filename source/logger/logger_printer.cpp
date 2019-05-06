#include "eul/logger/logger_printer.hpp"

#include "eul/logger/logger_stream_registry.hpp"
#include "eul/time/i_time_provider.hpp"
#include "eul/utils/string.hpp"

#include <iostream>

namespace eul
{
namespace logger
{

logger_printer::logger_printer(
    const std::string_view& prefix,
    const std::string_view& name,
    const time::i_time_provider& time)
    : name_(name)
    , time_(time)
{
    printHeader(prefix);
}

logger_printer::~logger_printer()
{
    write_to_streams("\n");
}

const logger_printer& logger_printer::operator<<(const std::string_view& str) const
{
    write_to_streams(str);
    return *this;
}

const logger_printer& logger_printer::operator<<(int data) const
{
    char number[21];
    utils::itoa(data, number);
    write_to_streams(number);
    return *this;
}

void logger_printer::printHeader(std::string_view level) const
{
    write_to_streams("<");
    printTimeAndDate();
    write_to_streams("> ");
    write_to_streams(level);
    write_to_streams("/");
    write_to_streams(name_);
    write_to_streams(": ");
}

void logger_printer::printTimeAndDate() const
{
    constexpr const int BufferSize = 30;
    char buffer[BufferSize];
    std::time_t t          = time_.milliseconds().count() / 1000;
    struct tm* currentTime = std::localtime(&t);

    utils::formatDateAndTime(buffer, BufferSize, currentTime);
    write_to_streams(buffer);
}

void logger_printer::write_to_streams(const std::string_view& data) const
{
    for (auto& stream : logger_stream_registry::get().get_streams())
    {
        stream.data()->write(data);
    }
}


} // namespace logger
} // namespace eul
