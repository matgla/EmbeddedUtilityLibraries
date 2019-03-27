cmake_minimum_required(VERSION 3.1)

project(eul CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Eul_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE STRING "path to EUL sources" FORCE)

add_library(eul INTERFACE)
target_sources(eul INTERFACE
    "${PROJECT_SOURCE_DIR}/include/eul/event_loop.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/function.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/memory_ptr.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/observer.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node_const_iterator.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node_iterator.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_list.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/container/observable/observing_node.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/traits.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/utils.hpp"
)

add_subdirectory(lib)

add_subdirectory(include/eul/logger)
add_subdirectory(include/eul/timer)
add_subdirectory(include/eul/mpl)

target_include_directories(eul INTERFACE ${Eul_INCLUDE_DIR})
target_link_libraries(eul INTERFACE eul_logger eul_mpl eul_timer gsl)

if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)
