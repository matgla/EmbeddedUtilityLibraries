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

add_library(eul_timer INTERFACE)

set (include_dir ${PROJECT_SOURCE_DIR}/include/timer/eul/timer)

target_sources(eul_timer
    INTERFACE
        ${include_dir}/interval_timer.hpp
        ${include_dir}/ITimer.hpp
        ${include_dir}/observed_timer.hpp
        ${include_dir}/timeout_timer.hpp
        ${include_dir}/timer_manager.hpp
        ${include_dir}/timer.hpp
)

target_include_directories(eul_timer INTERFACE ${PROJECT_SOURCE_DIR}/include/timer)

target_link_libraries(eul_timer
    INTERFACE
        eul_time
        eul_public_flags
        eul_container
        eul_functional
)

