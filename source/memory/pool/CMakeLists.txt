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

add_library(eul_memory_pool INTERFACE)

set (include_dir ${PROJECT_SOURCE_DIR}/include/memory/eul/memory/pool)

target_sources(eul_memory_pool
    INTERFACE
        ${include_dir}/details/allocation_header.hpp
        ${include_dir}/memory_pool.hpp
        ${include_dir}/unique_ptr.hpp
)

target_include_directories(eul_memory_pool 
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/include/memory 
)

target_link_libraries(eul_memory_pool 
    INTERFACE 
        eul_public_flags
)

