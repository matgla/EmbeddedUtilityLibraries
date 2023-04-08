add_library(eul_error STATIC)
add_library(eul::error ALIAS eul_error)

set (include_dir ${PROJECT_SOURCE_DIR}/include/error/eul/error)

target_sources(eul_error
    PUBLIC
        ${include_dir}/error_code.hpp
        ${include_dir}/error_category.hpp
        ${include_dir}/error_condition.hpp
        ${include_dir}/system_category.hpp
        ${include_dir}/generic_category.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/error_code.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/error_condition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/error_category.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/system_category.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generic_category.cpp
)

target_include_directories(eul_error PUBLIC ${PROJECT_SOURCE_DIR}/include/error)

target_link_libraries(eul_error 
    PUBLIC 
        eul_public_flags 
    PRIVATE 
        eul_utils
        eul_private_flags
)
