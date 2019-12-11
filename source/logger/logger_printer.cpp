// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "eul/logger/logger_printer.hpp"

#include "eul/logger/logger_stream_registry.hpp"
#include "eul/time/i_time_provider.hpp"
#include "eul/utils/string.hpp"

namespace eul
{
namespace logger
{

logger_printer::logger_printer(
    const std::string_view& prefix,
    const std::string_view& name,
    const std::string_view& user_prefix,
    const time::i_time_provider& time)
    : name_(name)
    , time_(time)
{
    printHeader(prefix, user_prefix);
}

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

logger_printer& logger_printer::operator<<(const std::string_view& str)
{
    write_to_streams(str);
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

void logger_printer::printHeader(std::string_view level, std::string_view user_prefix) const
{
    write_to_streams("<");
    printTimeAndDate();
    write_to_streams("> ");
    write_to_streams(level);
    write_to_streams("/");
    write_to_streams(user_prefix);
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

int logger_printer::get_base() const
{
    switch (flags_.get_base())
    {
        case logging_flags::base::dec:
        {
            return 10;
        } break;
        case logging_flags::base::hex:
        {
            return 16;
        } break;
        case logging_flags::base::oct:
        {
            return 8;
        } break;
        case logging_flags::base::bin:
        {
            return 2;
        } break;
    }
    return 0;
}

} // namespace logger
} // namespace eul
