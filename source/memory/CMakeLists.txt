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

add_subdirectory(pool)

add_library(eul_memory INTERFACE)
add_library(eul::memory ALIAS eul_memory)

set (include_dir ${PROJECT_SOURCE_DIR}/include/memory/eul/memory)

target_sources(eul_memory
    INTERFACE
        ${include_dir}/memory_ptr.hpp
        ${include_dir}/observer.hpp 
        ${include_dir}/round_memory_pool.hpp
)

target_include_directories(eul_memory
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/memory
)

target_link_libraries(eul_memory
    INTERFACE 
        eul_public_flags
)

