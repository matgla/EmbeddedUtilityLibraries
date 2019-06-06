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