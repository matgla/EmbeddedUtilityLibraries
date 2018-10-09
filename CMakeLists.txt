cmake_minimum_required(VERSION 3.1)

project(eul CXX)

set(Eul_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE STRING "path to EUL sources" FORCE)

add_library(eul INTERFACE)
target_sources(eul INTERFACE
    "${PROJECT_SOURCE_DIR}/include/eul/event_loop.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/function.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/logger.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/ability.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/access.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/data.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/filter.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/inherit_from.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/interface.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/object.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/mixin/type.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/mpl/tuples/for_each.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/traits.hpp"
    "${PROJECT_SOURCE_DIR}/include/eul/utils.hpp"
)

target_include_directories(eul INTERFACE ${Eul_INCLUDE_DIR})

if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)
