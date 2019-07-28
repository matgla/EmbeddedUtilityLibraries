add_library(eul_kernel)

target_sources(eul_kernel
    INTEFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fwd.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/kernel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/module.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/typeid.hpp
)

target_include_directories(eul_kernel INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_compile_options(eul_kernel INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror -fPIC>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)