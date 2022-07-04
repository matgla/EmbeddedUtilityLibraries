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

add_executable (eul_crc_tests)

target_sources (eul_crc_tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/CrcTestBase.hpp
        
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc3Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc4Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc5Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc6Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc7Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc8Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc10Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc11Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc12Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc13Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc14Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc15Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc16Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc17Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc21Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc24Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc30Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc31Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc32Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc40Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crc64Tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CrcUtilsTests.cpp
)

target_link_libraries (eul_crc_tests 
    PRIVATE 
        eul::crc
        eul_private_flags 
        gtest_main
)

add_test (crc_tests eul_crc_tests)
add_dependencies (check eul_crc_tests)

