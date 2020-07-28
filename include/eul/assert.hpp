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

#ifndef NDEBUG

#include <cstdlib>
#include <string_view>

#include "utils/unused.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define EUL_ASSERT_MSG(expr, msg)                                                                            \
    ((expr) ? (void)0 : eul::assertFailed(#expr, std::string_view(__FILE__), __LINE__, std::string_view(&__FUNCTION__[0], sizeof(__FUNCTION__)), std::string_view(msg)))

namespace eul
{


inline void assertFailed(const char* expr, std::string_view file, int line, std::string_view function, std::string_view msg)
{
    UNUSED5(expr, file, line, function, msg);
}

} // namespace eul

#else

#define EUL_ASSERT_MSG(expr, msg) ((void)(0))

#endif // ASSERTION_ENABLED
