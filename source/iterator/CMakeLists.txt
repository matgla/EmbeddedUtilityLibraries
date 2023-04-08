# This file is part of EmbeddedUtilityLibraries project. This project is set of libraries useful for embedded development.
# Copyright (C) 2021 Mateusz Stadnik
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

add_library(eul_iterator INTERFACE)
add_library(eul::iterator ALIAS eul_iterator)

set (include_dir ${PROJECT_SOURCE_DIR}/include/iterator/eul/iterator)

target_sources(eul_iterator
    INTERFACE
        ${include_dir}/counting_const_iterator.hpp
        ${include_dir}/counting_iterator.hpp
)

target_include_directories(eul_iterator
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/iterator
)

target_link_libraries(eul_iterator
    INTERFACE 
        eul_public_flags
)

