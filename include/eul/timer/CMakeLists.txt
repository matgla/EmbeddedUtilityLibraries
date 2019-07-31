add_library(eul_timer INTERFACE)

target_sources(eul_timer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/interval_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ITimer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/observed_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timeout_timer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.hpp
)

target_include_directories(eul_timer INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(eul_timer
    INTERFACE
        eul_time
)

target_compile_options(eul_timer INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)