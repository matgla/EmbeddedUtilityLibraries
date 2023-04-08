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

add_library(eul_mpl_types INTERFACE)
add_library(eul::mpl::types ALIAS eul_mpl_types)

set (include_dir ${PROJECT_SOURCE_DIR}/include/mpl/types/eul/mpl/types)

target_sources(eul_mpl_types
    INTERFACE
        ${include_dir}/get_index_of_binded_key.hpp
        ${include_dir}/binded_traits.hpp
        ${include_dir}/bind_type.hpp
        ${include_dir}/traits.hpp
)

target_include_directories(eul_mpl_types
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/mpl/types
)

target_link_libraries(eul_mpl_types 
    INTERFACE 
        eul_public_flags
)


