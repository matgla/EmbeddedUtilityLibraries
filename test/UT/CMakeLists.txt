include_directories(../lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR})

set (test_sources
    container/observable/ObservingListTests.cpp
    container/RingBufferTests.cpp
    container/StaticVectorTests.cpp
    container/StaticDequeTests.cpp
    container/iterator/IndexConstIteratorTests.cpp
    container/iterator/IndexIteratorTests.cpp
    mpl/types/BindTypeTests.cpp
    kernel/KernelTests.cpp
    EventLoopTests.cpp
    ExecutionQueueTests.cpp
    FunctionTests.cpp
    MemoryPoolTests.cpp
    mpl/types/BindTypeTests.cpp
    mpl/types/GetIndexOfBindedKeyTests.cpp
    mpl/tuples/ExtendTests.cpp
    mpl/tuples/FilterTests.cpp
    mpl/mixin/InheritFromTests.cpp
    mpl/mixin/MixinTests.cpp
    timer/TimeoutTimerTests.cpp
    timer/TimerManagerTests.cpp
    timer/TimerTests.cpp
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
target_link_libraries(eul_tests eul test_stubs)

add_custom_target(run_eul_ut
  COMMAND "${CMAKE_BINARY_DIR}/test/UT/eul_tests"
  DEPENDS eul_tests
)
