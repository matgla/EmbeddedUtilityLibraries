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

add_executable (eul_error_tests EXCLUDE_FROM_ALL)

target_sources (eul_error_tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/ErrorCategoryTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ErrorCodeTests.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/ErrorConditionTests.cpp
)

target_link_libraries (eul_error_tests 
    PRIVATE 
        eul_error
        eul_private_flags 
        catch
)

add_test (error_tests eul_error_tests)
add_dependencies (check eul_error_tests)

