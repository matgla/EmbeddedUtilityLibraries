add_library(eul_mpl INTERFACE)

add_subdirectory(mixin)
add_subdirectory(tuples)
add_subdirectory(types)

target_link_libraries(eul_mpl
    INTERFACE
        eul_mpl_mixin
        eul_mpl_tuples
        eul_mpl_types
)

target_include_directories(eul_mpl_tuples
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)