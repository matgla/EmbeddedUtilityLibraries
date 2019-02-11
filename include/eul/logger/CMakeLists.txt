add_library(eul_logger INTERFACE)

target_sources(eul_logger
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include/eul/logger/logger.hpp"
        "${PROJECT_SOURCE_DIR}/include/eul/logger/logger_factory.hpp"
        "${PROJECT_SOURCE_DIR}/include/eul/logger/logger_policy.hpp"
        "${PROJECT_SOURCE_DIR}/include/eul/logger/logger_traits.hpp"
)

target_include_directories(eul_logger INTERFACE "${PROJECT_SOURCE_DIR}/include")

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

target_compile_definitions(eul_logger INTERFACE
    ${logging_definition}
)
