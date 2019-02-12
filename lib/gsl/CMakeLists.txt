file(GLOB_RECURSE gsl_srcs
    "gsl/include/*."
    )

set(Gsl_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/gsl/gsl/include" CACHE STRING "path to GSL sources" FORCE)

add_library(gsl INTERFACE)
target_sources(gsl INTERFACE ${gsl_srcs})
target_include_directories(gsl INTERFACE ${Gsl_INCLUDE_DIR})
