add_library(eul_filesystem STATIC)

target_sources(eul_filesystem
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/filesystem/path.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/path_const_iterator.cpp
)

target_include_directories(eul_filesystem PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_options(eul_filesystem PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${eul_cxx_compilation_flags} -std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(eul_filesystem PRIVATE
    ${eul_cxx_linking_flags}
)

add_library(eul_filesystem_interface INTERFACE)
target_sources(eul_filesystem_interface
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/eul/filesystem/path.hpp
)
target_include_directories(eul_filesystem_interface INTERFACE "${PROJECT_SOURCE_DIR}/include")
