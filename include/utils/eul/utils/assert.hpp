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

#include <source_location>

#include "eul/utils/unused.hpp"
#include <cstdlib>
#include <string_view>


#ifndef NDEBUG
namespace eul
{

inline void assertFailed(const char* expr, std::string_view file, uint32_t line, std::string_view function,
                         std::string_view msg)
{
    UNUSED5(expr, file, line, function, msg);
}

} // namespace eul
constexpr void eul_assert_msg(const auto value, const std::string_view msg,
                              const std::source_location loc = std::source_location::current())
{
    if (!value)
    {
        eul::assertFailed(loc.function_name(), loc.file_name(), loc.line(), loc.function_name(), msg);
    }
}

#else

constexpr void eul_assert_msg(const auto value, const std::string_view msg,
                              const std::source_location loc = std::source_location::current())
{
    UNUSED(value, msg, loc);
}

#endif // ASSERTION_ENABLED
