add_library(test_stubs INTERFACE)

target_sources(test_stubs
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/time/TimeStub.hpp
)
