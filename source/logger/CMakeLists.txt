add_library(eul_logger STATIC)
add_library(eul::logger ALIAS eul_logger)

set (include_dir ${PROJECT_SOURCE_DIR}/include/logger/eul/logger)

target_sources(eul_logger
    PUBLIC
        ${include_dir}/logger.hpp
        ${include_dir}/logger_factory.hpp 
        ${include_dir}/logger_policy.hpp 
        ${include_dir}/logger_printer.hpp 
        ${include_dir}/logger_stream.hpp 
        ${include_dir}/logger_stream_registry.hpp
        ${include_dir}/suppressing_logger.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_factory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_printer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_stream_registry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_stream.cpp
)

target_include_directories(eul_logger PUBLIC ${PROJECT_SOURCE_DIR}/include/logger)

if (LOG_LEVEL STREQUAL "Trace")
    set(logging_definition "LOG_LEVEL_TRACE")
elseif (LOG_LEVEL STREQUAL "Debug")
    set(logging_definition "LOG_LEVEL_DEBUG")
elseif (LOG_LEVEL STREQUAL "Info")
    set(logging_definition "LOG_LEVEL_INFO")
elseif (LOG_LEVEL STREQUAL "Warning")
    set(logging_definition "LOG_LEVEL_WARNING")
elseif (LOG_LEVEL STREQUAL "Error")
    set(logging_definition "LOG_LEVEL_ERROR")
else ()
    set(logging_definition "LOG_LEVEL_DISABLED")
endif()

message (STATUS "Logging level: ${logging_definition}")

target_compile_definitions(eul_logger PUBLIC
    ${logging_definition}
)

target_link_libraries(eul_logger
    PUBLIC
        eul_utils
        eul_container
        eul_time
        eul_public_flags 
    PRIVATE 
        eul_private_flags
)

