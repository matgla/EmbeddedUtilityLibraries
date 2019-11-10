add_library(eul_utils INTERFACE)

target_sources(eul_utils
    INTERFACE  
        ${PROJECT_SOURCE_DIR}/include/eul/utils/math.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/string.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/unused.hpp

        #        ${CMAKE_CURRENT_SOURCE_DIR}/math.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/string.cpp
)

target_include_directories(eul_utils INTERFACE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(eul_utils
    INTERFACE 
        gsl
)

target_compile_options(eul_utils INTERFACE 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror ${cxx_flags_shared_library}>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)
