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

add_library(eul_time INTERFACE)

set (include_dir ${PROJECT_SOURCE_DIR}/include/time/eul/time)

target_sources(eul_time
    INTERFACE
        ${include_dir}/fwd.hpp
        ${include_dir}/i_time_provider.hpp
)

target_include_directories(eul_time INTERFACE ${PROJECT_SOURCE_DIR}/include/time)

target_link_libraries(eul_time 
    INTERFACE 
        eul_public_flags
)

