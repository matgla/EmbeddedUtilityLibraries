add_library(eul_error STATIC)

target_sources(eul_error
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/error/error_code.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/error/error_category.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/error/error_condition.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/error/system_category.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/error/generic_category.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/error_code.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/error_condition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/error_category.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/system_category.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generic_category.cpp
)

target_include_directories(eul_error PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_options(eul_error PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${eul_cxx_compilation_flags} -std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(eul_error PUBLIC
    ${eul_cxx_linking_flags}
)
