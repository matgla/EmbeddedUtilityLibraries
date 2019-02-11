add_library(eul_mpl_types INTERFACE)

target_sources(eul_mpl_types
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/get_index_of_binded_key.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/binded_traits.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bind_type.hpp
)

target_include_directories(eul_mpl_types
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
