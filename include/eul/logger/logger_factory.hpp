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
