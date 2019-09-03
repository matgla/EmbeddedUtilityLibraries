add_library(eul_std INTERFACE)

if (NO_STDCXX)
message (STATUS "NO_STDCXX active, providing custom std implementation")
target_sources(eul_std
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/eul/std/cmath
        ${PROJECT_SOURCE_DIR}/include/eul/std/cstdint
        ${PROJECT_SOURCE_DIR}/include/eul/std/ctime
        ${PROJECT_SOURCE_DIR}/include/eul/std/type_traits
        ${PROJECT_SOURCE_DIR}/include/eul/std/utility
)

target_compile_options(eul_std INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

message("${PROJECT_SOURCE_DIR}/include/eul/std")
target_include_directories(eul_std INTERFACE "${PROJECT_SOURCE_DIR}/include/eul/std")

endif()
