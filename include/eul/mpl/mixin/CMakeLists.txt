add_library(eul_mpl_mixin INTERFACE)

target_sources(eul_mpl_mixin
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/ability.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/access.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/const_access.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/name.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/inherit_from.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interface.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/type.hpp
)

target_include_directories(eul_mpl_mixin INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(eul_mpl_mixin
    INTERFACE
        eul_mpl_tuples
)
