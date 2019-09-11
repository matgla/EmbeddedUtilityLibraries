include (../cmake/GitModules.cmake)

add_definitions("-DGSL_TERMINATE_ON_CONTRACT_VIOLATION=1 -DGSL_MSVC_USE_STL_NOEXCEPTION_WORKAROUND")
fetch_module_via_tag(lib/gsl/gsl ${PROJECT_SOURCE_DIR}/lib/gsl ${PROJECT_SOURCE_DIR} "v2.0.0")
