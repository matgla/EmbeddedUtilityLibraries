include_directories(../lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set (test_sources
    EventLoopTests.cpp
    FunctionTests.cpp
    MemoryPoolTests.cpp
    Runner.cpp
    mpl/mixin/FilterTests.cpp
    mpl/mixin/InheritFromTests.cpp
    mpl/mixin/MixinTests.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++17 -Wall -Wextra -fconcepts")

if (TEST_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif (TEST_COVERAGE)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)

add_executable(eul_tests ${test_sources})
target_link_libraries(eul_tests eul)
enable_testing()

add_custom_target(run_eul_ut
  COMMAND "${CMAKE_BINARY_DIR}/test/UT/eul_tests"
  DEPENDS eul_tests
)
