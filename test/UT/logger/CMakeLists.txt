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

add_executable (eul_logger_tests)

add_library(eul_logger_disabled_policy_tests OBJECT)
target_sources(eul_logger_disabled_policy_tests
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/LoggerTestsDisabledPolicy.cpp
)
target_link_libraries(eul_logger_disabled_policy_tests
    PUBLIC 
        Catch2
        eul_logger
        eul_private_flags
)

add_library(eul_logger_error_policy_tests OBJECT)
target_sources(eul_logger_error_policy_tests
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/LoggerTestsErrorPolicy.cpp
)
target_compile_definitions(eul_logger_error_policy_tests
    PRIVATE 
        -DLOG_LEVEL_ERROR=1
)
target_link_libraries(eul_logger_error_policy_tests
    PUBLIC 
        Catch2
        eul_logger
        eul_private_flags
)

target_sources (eul_logger_tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/ExpectStream.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TimeProviderStub.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/ExpectStream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TimeProviderStub.cpp

        $<TARGET_OBJECTS:eul_logger_disabled_policy_tests>
        $<TARGET_OBJECTS:eul_logger_error_policy_tests>
)

target_link_libraries (eul_logger_tests 
    PRIVATE 
        Catch2WithMain
        eul_logger
)

add_test (logger_tests eul_logger_tests)
add_dependencies (check eul_logger_tests)

