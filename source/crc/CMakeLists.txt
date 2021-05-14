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

add_library(eul_crc INTERFACE)

set (include_dir ${PROJECT_SOURCE_DIR}/include/crc/eul/crc)

target_sources(eul_crc
    INTERFACE
        ${include_dir}/crc.hpp
)

target_include_directories(eul_crc
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/crc
)

target_link_libraries(eul_crc 
    INTERFACE 
        eul_public_flags
)

