cmake_minimum_required(VERSION 3.1)

project(eul CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Eul_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE STRING "path to EUL sources" FORCE)

add_library(eul)
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

add_subdirectory(lib)

add_subdirectory(source/logger)
add_subdirectory(source/utils)
add_subdirectory(include/eul/execution)
add_subdirectory(include/eul/time)
add_subdirectory(include/eul/timer)
add_subdirectory(include/eul/mpl)

target_include_directories(eul PUBLIC ${Eul_INCLUDE_DIR})
target_link_libraries(eul
    PUBLIC
        eul_mpl
        eul_timer
        eul_time
        eul_execution
        -Wl,--whole-archive
            eul_logger
            eul_utils
        -Wl,--no-whole-archive
        gsl)

target_compile_options(${library_name} INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
    $<$<CONFIG:DEBUG>:-O0 -g>
    $<$<CONFIG:RELEASE>:-Os>
)

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