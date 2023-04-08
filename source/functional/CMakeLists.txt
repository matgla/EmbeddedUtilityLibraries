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

add_library(eul_functional INTERFACE)
add_library(eul::functional ALIAS eul_functional)

set (include_dir ${PROJECT_SOURCE_DIR}/include/functional/eul/functional)

target_sources(eul_functional
    INTERFACE
        ${include_dir}/function.hpp
)

target_include_directories(eul_functional
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/functional
)

target_link_libraries(eul_functional
    INTERFACE 
        eul_public_flags
        eul_utils
)

