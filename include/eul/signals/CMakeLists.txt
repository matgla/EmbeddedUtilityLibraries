add_library(eul_signals INTERFACE)

target_sources(eul_signals
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/signal.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/slot.hpp
)

target_include_directories(eul_signals
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(eul_signals
    INTERFACE
        eul
)

target_compile_options(eul_signals INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)