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

cmake_minimum_required(VERSION 3.2)

project(eul CXX)

# EUL for apple supports only libc++
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

find_package(CMakeUtils REQUIRED)

include (sanitizers)
add_sanitizers()
include (coverage) 
add_coverage()

add_library(eul_public_flags INTERFACE)
add_library(eul_private_flags INTERFACE)

if (MSVC)
    target_compile_options(eul_public_flags INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:/std:c++latest ${eul_cxx_compilation_flags}>
    )
    target_compile_options(eul_private_flags INTERFACE
        /W4 /WX 
        $<$<CONFIG:DEBUG>:/Od> 
        $<$<CONFIG:RELEASE>:/O2>
    )
else ()
    target_compile_options(eul_public_flags INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++20 ${eul_cxx_compilation_flags}>
    )
    target_compile_options(eul_private_flags INTERFACE
        -Wall -Wpedantic -Werror -Wextra -pedantic-errors -Wconversion -Wsign-conversion
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-O2>
    )
    target_link_libraries(eul_private_flags INTERFACE eul_public_flags)
endif ()

target_link_libraries(eul_public_flags 
    INTERFACE 
        enable_sanitizers 
        coverage_flags
)

target_link_libraries(eul_private_flags 
    INTERFACE 
        enable_sanitizers 
        coverage_flags
)

target_link_options(eul_private_flags INTERFACE ${eul_cxx_linking_flags})

add_subdirectory (source/container)
add_subdirectory (source/crc)
add_subdirectory (source/error)
add_subdirectory (source/execution)
add_subdirectory (source/filesystem)
add_subdirectory (source/functional)
add_subdirectory (source/iterator)
add_subdirectory (source/kernel)
add_subdirectory (source/logger)
add_subdirectory (source/memory)
add_subdirectory (source/math)
add_subdirectory (source/mpl)
add_subdirectory (source/signals)
add_subdirectory (source/time)
add_subdirectory (source/timer)
add_subdirectory (source/utils)

if (NOT DISABLE_TESTS)
    include (CTest)
    add_subdirectory(test)
endif ()

if (ENABLE_CLANG_TIDY)
    message (STATUS "Enabled ClangTidy")
    include(virtualenv)

    setup_virtualenv(clang_tidy_venv ${PROJECT_SOURCE_DIR}/requirements.txt)

    find_program(RUN_CLANG_TIDY_EXE NAMES "run-clang-tidy" REQUIRED)

    add_custom_target(filter_out_compile_commands 
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/clang_tidy_venv/bin/compile-commands --file ${PROJECT_BINARY_DIR}/compile_commands.json 
            --filter_files=".*_deps/.*"
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
    )

    cmake_host_system_information(RESULT cpus QUERY NUMBER_OF_LOGICAL_CORES)

    add_custom_target(run_clang_tidy
        DEPENDS filter_out_compile_commands
        COMMAND ${RUN_CLANG_TIDY_EXE} -j${cpus}
        VERBATIM
    )

    add_custom_command(OUTPUT clang_tidy_report.txt
        COMMAND ${RUN_CLANG_TIDY_EXE} -j${cpus} > clang_tidy_report.txt
        DEPENDS filter_out_compile_commands
        VERBATIM
    )

    add_custom_target(run_clang_tidy_for_sonar
        DEPENDS clang_tidy_report.txt
        VERBATIM
    )
endif()