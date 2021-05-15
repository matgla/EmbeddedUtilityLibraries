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

add_executable (eul_kernel_tests)

target_sources (eul_kernel_tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/KernelTests.cpp
)

target_link_libraries (eul_kernel_tests 
    PRIVATE 
        eul_kernel
        eul_private_flags 
        catch
)

add_test (kernel_tests eul_kernel_tests)
add_dependencies (check eul_kernel_tests)

