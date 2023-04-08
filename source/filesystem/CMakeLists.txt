add_library(eul_filesystem STATIC)
add_library(eul::filesystem ALIAS eul_filesystem)

set (include_dir ${PROJECT_SOURCE_DIR}/include/filesystem/eul/filesystem)

target_sources(eul_filesystem
    PUBLIC
        ${include_dir}/path.hpp
        ${include_dir}/path_const_iterator.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/path_const_iterator.cpp
)

target_include_directories(eul_filesystem PUBLIC ${PROJECT_SOURCE_DIR}/include/filesystem)

target_link_libraries (eul_filesystem
    PUBLIC 
        eul_public_flags 
    PRIVATE 
        eul_private_flags
)

