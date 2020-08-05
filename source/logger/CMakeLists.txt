add_library(eul_logger STATIC)

target_sources(eul_logger
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/logger/logger_policy.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/logger/logger_stream_registry.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/logger/logger_stream.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/logger/logger.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_factory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_printer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_stream_registry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logger_stream.cpp
)

target_include_directories(eul_logger PUBLIC "${PROJECT_SOURCE_DIR}/include")

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
        GSL
)


target_compile_options(eul_logger PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${eul_cxx_compilation_flags} -std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(eul_logger PUBLIC
   ${eul_cxx_linking_flags})
