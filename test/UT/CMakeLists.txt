# This file is part of EUL project. This project is set of libraries useful for embedded development.
# Copyright (C) 2019 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

include_directories(SYSTEM ../lib)
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
    crc/Crc32Tests.cpp
    error/ErrorCategoryTests.cpp
    error/ErrorCodeTests.cpp
    error/ErrorConditionTests.cpp
    filesystem/PathTests.cpp
    filesystem/PathConstIteratorTests.cpp
    mpl/types/BindTypeTests.cpp
    kernel/KernelTests.cpp
    EventLoopTests.cpp
    execution/ExecutionQueueTests.cpp
    FunctionTests.cpp
    MemoryPoolTests.cpp
    math/VectorTests.cpp
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
    signals/SignalTests.cpp
    Runner.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++2a -Wall -Wextra")

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
