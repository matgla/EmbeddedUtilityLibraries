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

add_library(eul_kernel INTERFACE)
add_library(eul::kernel ALIAS eul_kernel)

set (include_dir ${PROJECT_SOURCE_DIR}/include/kernel/eul/kernel)

target_sources(eul_kernel
    INTERFACE
        ${include_dir}/event_listener.hpp
        ${include_dir}/fwd.hpp
        ${include_dir}/kernel.hpp
        ${include_dir}/service.hpp
        ${include_dir}/typeid.hpp
)

target_include_directories(eul_kernel 
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/include/kernel 
)

target_link_libraries(eul_kernel
    INTERFACE 
        eul_public_flags
        eul_container
)

