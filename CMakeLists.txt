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

cmake_minimum_required(VERSION 3.1)

project(eul CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Eul_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE STRING "path to EUL sources" FORCE)

include(FetchContent)

FetchContent_Declare(
  mspkg
  GIT_REPOSITORY https://github.com/matgla/mspkg.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(mspkg)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mspkg_SOURCE_DIR}/cmake)
include (mspkg)

setup_mspkg(${mspkg_SOURCE_DIR})

find_package(GSL REQUIRED)
find_package(CMakeUtils REQUIRED)

add_library(eul STATIC)
target_sources(eul PUBLIC
    "${PROJECT_SOURCE_DIR}/include/eul/event_loop.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/function.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/memory_ptr.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/observer.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node_const_iterator.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node_iterator.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_list.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/traits.hpp"
)

add_subdirectory(source/logger)
add_subdirectory(source/utils)
add_subdirectory(source/error)
add_subdirectory(source/filesystem)
add_subdirectory(include/eul/execution)
add_subdirectory(include/eul/time)
add_subdirectory(include/eul/timer)
add_subdirectory(include/eul/mpl)
add_subdirectory(include/eul/memory)

target_include_directories(eul PUBLIC ${Eul_INCLUDE_DIR})
target_link_libraries(eul
    PRIVATE
        eul_mpl
        eul_timer
        eul_time
        eul_execution
        eul_logger
        eul_utils
        eul_error
        eul_filesystem
    PUBLIC
        GSL
    )

include (sanitizers)
add_asan_build_type()
add_lsan_build_type()
add_msan_build_type()
add_ubsan_build_type()

target_compile_options(eul PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a ${eul_cxx_compilation_flags}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(eul PUBLIC
    ${eul_cxx_linking_flags})

install (
    TARGETS
        eul
    DESTINATION
        ${CMAKE_BINARY_DIR}
    EXPORT
        eul.cmake
)

if (NOT DISABLE_TESTS)
    add_subdirectory(test)
endif ()
