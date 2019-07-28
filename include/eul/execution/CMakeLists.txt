add_library(eul_execution INTERFACE)

target_sources(eul_execution
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/execution_queue.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fwd.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/i_execution_queue.hpp
)

target_include_directories(eul_execution
    INTERFACE
        ${PROJECT_SOURCE_DIR}/source
)

target_link_libraries(eul_execution
    INTERFACE
        eul
)

target_compile_options(eul_execution INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror -fPIC>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)