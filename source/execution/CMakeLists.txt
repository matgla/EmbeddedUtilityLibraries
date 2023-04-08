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

add_library(eul_execution INTERFACE)
add_library(eul::execution ALIAS eul_execution)

set (include_dir ${PROJECT_SOURCE_DIR}/include/execution/eul/execution)

target_sources(eul_execution
    INTERFACE
        ${include_dir}/event_loop.hpp
        ${include_dir}/execution_queue.hpp
        ${include_dir}/fwd.hpp
        ${include_dir}/i_execution_queue.hpp
)

target_include_directories(eul_execution
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/execution
)

target_link_libraries(eul_execution 
    INTERFACE 
        eul_public_flags
        eul_container
        eul_functional
)

