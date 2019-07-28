add_library(eul_time INTERFACE)

target_sources(eul_time
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/i_time_provider.hpp
)

target_include_directories(eul_time INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_compile_options(eul_time INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)