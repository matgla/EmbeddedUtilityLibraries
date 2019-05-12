file(GLOB_RECURSE gsl_srcs
    "gsl/include/*."
)

set(Gsl_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gsl/include" CACHE STRING "path to GSL sources" FORCE)

message (STATUS "Added library: ${Gsl_INCLUDE_DIR}")

add_library(gsl INTERFACE)
target_sources(gsl INTERFACE ${gsl_srcs})
target_include_directories(gsl INTERFACE ${Gsl_INCLUDE_DIR})
