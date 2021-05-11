add_library(eul_filesystem STATIC)

target_sources(eul_filesystem
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/filesystem/path.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/path_const_iterator.cpp
)

target_include_directories(eul_filesystem PUBLIC "${PROJECT_SOURCE_DIR}/include")

if (MSVC)
    target_compile_options(eul_filesystem PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:/W4 /WX /std:c++latest ${eul_cxx_compilation_flags}>
    )
else ()
    target_compile_options(eul_filesystem PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a ${eul_cxx_compilation_flags}>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    )
endif ()

target_link_options(eul_filesystem PRIVATE
    ${eul_cxx_linking_flags}
)
