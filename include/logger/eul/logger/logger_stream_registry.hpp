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

#pragma once

#include "eul/container/observable/observing_list.hpp"

#include "eul/logger/logger_stream.hpp"
#include "eul/logger/logger_stream_registry.hpp"

namespace eul::logger 
{

class logger_stream_registry
{
public:
    using stream_node = eul::container::observing_node<logger_stream*>;
    using streams = eul::container::observing_list<stream_node>;
    static logger_stream_registry& get();
    void register_stream(logger_stream& stream);

    streams& get_streams();


private:
    logger_stream_registry() = default;

    streams streams_;
};

} // namespace eul::logger
