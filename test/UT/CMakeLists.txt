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

add_library (catch INTERFACE)

target_sources (catch INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Runner.cpp
)

target_include_directories (catch 
    SYSTEM 
    INTERFACE 
    ${PROJECT_SOURCE_DIR}/test/lib
)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -V)

add_subdirectory (container)
add_subdirectory (crc)
add_subdirectory (error)
add_subdirectory (execution)
add_subdirectory (filesystem)
add_subdirectory (functional)
add_subdirectory (kernel)
add_subdirectory (math)
add_subdirectory (memory)
add_subdirectory (mpl)
add_subdirectory (signals)
add_subdirectory (timer)
add_subdirectory (utils)

