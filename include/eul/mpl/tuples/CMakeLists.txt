add_library(eul_mpl_tuples INTERFACE)

target_sources(eul_mpl_tuples
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/extend.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/filter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/for_each.hpp
)

target_include_directories(eul_mpl_tuples
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
