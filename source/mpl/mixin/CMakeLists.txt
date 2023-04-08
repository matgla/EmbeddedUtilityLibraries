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

add_library(eul_mpl_mixin INTERFACE)
add_library(eul::mpl::mixin ALIAS eul_mpl_mixin)

set (include_dir ${PROJECT_SOURCE_DIR}/include/mpl/mixin/eul/mpl/mixin)

target_sources(eul_mpl_mixin
    INTERFACE
        ${include_dir}/ability.hpp
        ${include_dir}/access.hpp
        ${include_dir}/const_access.hpp
        ${include_dir}/data.hpp
        ${include_dir}/name.hpp
        ${include_dir}/inherit_from.hpp
        ${include_dir}/interface.hpp
        ${include_dir}/object.hpp
        ${include_dir}/type.hpp
)

target_include_directories(eul_mpl_mixin INTERFACE ${PROJECT_SOURCE_DIR}/include/mpl/mixin)

target_link_libraries(eul_mpl_mixin
    INTERFACE
        eul_public_flags
        eul_mpl_tuples
)
