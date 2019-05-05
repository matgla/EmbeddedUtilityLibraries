add_library(eul_utils)

target_sources(eul_utils
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/eul/utils/math.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/string.hpp
        ${PROJECT_SOURCE_DIR}/include/eul/utils/unused.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/string.cpp
)

target_include_directories(eul_utils PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(eul_utils
    PUBLIC
        gsl
)
