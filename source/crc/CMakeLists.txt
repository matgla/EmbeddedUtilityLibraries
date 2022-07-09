# This file is part of EmbeddedUtilityLibraries project. 
# This project is set of libraries useful for embedded development.
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
add_library(eul::crc ALIAS eul_crc)

set (include_dir ${PROJECT_SOURCE_DIR}/include/crc/eul/crc)

target_sources(eul_crc
    INTERFACE
        ${include_dir}/detail/crc_utils.hpp
        ${include_dir}/crc_factory.hpp
        ${include_dir}/crc.hpp
        ${include_dir}/crc3.hpp
        ${include_dir}/crc4.hpp
        ${include_dir}/crc5.hpp
        ${include_dir}/crc6.hpp
        ${include_dir}/crc7.hpp
        ${include_dir}/crc8.hpp
        ${include_dir}/crc10.hpp
        ${include_dir}/crc11.hpp
        ${include_dir}/crc12.hpp
        ${include_dir}/crc13.hpp
        ${include_dir}/crc14.hpp
        ${include_dir}/crc15.hpp
        ${include_dir}/crc16.hpp
        ${include_dir}/crc17.hpp
        ${include_dir}/crc21.hpp
        ${include_dir}/crc24.hpp
        ${include_dir}/crc30.hpp
        ${include_dir}/crc31.hpp
        ${include_dir}/crc32.hpp
        ${include_dir}/crc40.hpp
        ${include_dir}/crc64.hpp
)

target_include_directories(eul_crc
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/crc
)

target_link_libraries(eul_crc 
    INTERFACE 
        eul_public_flags
        eul_utils
)

