cmake_minimum_required(VERSION 3.1)

project(eul CXX)

file(GLOB_RECURSE eul_srcs
    "include/eul/function.hpp"
    "include/eul/event_loop.hpp"
    )

set(Eul_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE STRING "path to EUL sources" FORCE)

add_library(eul INTERFACE)
target_sources(eul INTERFACE ${eul_srcs})
target_include_directories(eul INTERFACE ${Eul_INCLUDE_DIR})

if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)