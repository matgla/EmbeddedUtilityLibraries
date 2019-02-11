add_library(eul_memory_pool INTERFACE)

target_sources(eul_memory_pool
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool.hpp
)