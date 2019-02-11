include_directories(../lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set (test_sources
    container/observable/ObservingListTests.cpp
    container/RingBufferTests.cpp
    container/StaticVectorTests.cpp
    EventLoopTests.cpp
    FunctionTests.cpp
    MemoryPoolTests.cpp
    mpl/mixin/FilterTests.cpp
    mpl/mixin/InheritFromTests.cpp
    mpl/mixin/MixinTests.cpp
    ObserverTests.cpp
    Runner.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++2a -Wall -Wextra -fconcepts")

if (TEST_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(DEBUG 1)
endif (TEST_COVERAGE)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")
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
