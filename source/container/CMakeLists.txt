# This file is part of eul project.
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

add_library (eul_container INTERFACE)

set (include_dir ${PROJECT_SOURCE_DIR}/include/container/eul/container)

target_sources (eul_container 
    INTERFACE 
        ${include_dir}/iterator/index_const_iterator.hpp 
        ${include_dir}/iterator/index_iterator.hpp 
        ${include_dir}/observable/observing_list.hpp
        ${include_dir}/observable/observing_node.hpp 
        ${include_dir}/observable/observing_node_const_iterator.hpp 
        ${include_dir}/ring_buffer.hpp 
        ${include_dir}/static_deque.hpp 
        ${include_dir}/static_list.hpp 
        ${include_dir}/static_vector.hpp
)

target_link_libraries (eul_container 
    INTERFACE 
        eul_public_flags
        eul_utils
)

target_include_directories (eul_container 
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/include/container
)

