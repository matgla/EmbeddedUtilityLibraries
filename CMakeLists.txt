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

OPTION(BUILD_EXAMPLES OFF)

# EUL for apple supports only libc++
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  yaspem
  GIT_REPOSITORY https://github.com/matgla/yaspem.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(yaspem)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${yaspem_SOURCE_DIR}/cmake)
include (yaspem)
setup_yaspem(
    YASPEM_SOURCE ${yaspem_SOURCE_DIR}
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/packages
    PACKAGE_FILES ${PROJECT_SOURCE_DIR}/packages.json
)

find_package(CMakeUtils REQUIRED)

include (sanitizers)
add_sanitizers()
include (coverage) 
add_coverage()

if (${EUL_ENABLE_CLANG_TIDY})
  set (ENABLE_CLANG_TIDY ON) 
  include (clang_tidy)
  add_clang_tidy(".*packages/.*")
endif ()

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
        $<$<COMPILE_LANGUAGE:CXX>: ${eul_cxx_compilation_flags}>
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
    setup_yaspem(
        YASPEM_SOURCE ${yaspem_SOURCE_DIR}
        OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/packages
        PACKAGE_FILES ${PROJECT_SOURCE_DIR}/test/packages.json
    )

    add_subdirectory(test)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
