add_library(eul_utils STATIC)

target_sources(eul_utils
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/utils/math.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/string.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/unused.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/noncopyable.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/string.cpp
)

target_include_directories(eul_utils PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_options(eul_utils PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${eul_cxx_compilation_flags} -std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(eul_utils PUBLIC
    ${eul_cxx_linking_flags}
)
