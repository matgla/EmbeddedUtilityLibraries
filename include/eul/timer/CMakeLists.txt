# This file is part of EUL project. This project is set of libraries useful for embedded development.
# Copyright (C) 2019 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

add_library(eul_timer INTERFACE)

target_sources(eul_timer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/interval_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ITimer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/observed_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timeout_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.hpp
)

target_include_directories(eul_timer INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(eul_timer
    INTERFACE
        eul_time
)

if (MSVC)
    target_compile_options(eul_timer INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:/W4 /WX /std:c++latest ${eul_cxx_compilation_flags}>
    )
else ()
    target_compile_options(eul_timer INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a ${eul_cxx_compilation_flags}>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    )
endif ()