add_library(eul_utils STATIC)

set (include_dir ${PROJECT_SOURCE_DIR}/include/utils/eul/utils)

target_sources(eul_utils
    PUBLIC
        ${include_dir}/assert.hpp
        ${include_dir}/call.hpp
        ${include_dir}/math.hpp
        ${include_dir}/noncopyable.hpp
        ${include_dir}/string.hpp
        ${include_dir}/unused.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/string.cpp
)

target_include_directories(eul_utils PUBLIC ${PROJECT_SOURCE_DIR}/include/utils)

target_link_libraries(eul_utils 
    PUBLIC 
        eul_public_flags
    PRIVATE 
        eul_private_flags
)
