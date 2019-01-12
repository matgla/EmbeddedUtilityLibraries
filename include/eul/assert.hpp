#pragma once

#ifndef NDEBUG

#include <cstdlib>
#include <iostream>

#define EUL_ASSERT_MSG(expr, msg)                                                                            \
    ((expr) ? (void)0 : eul::assertFailed(#expr, __FILE__, __LINE__, __FUNCTION__, msg))

namespace eul
{


inline void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
    std::cerr << "Assertion failed (" << expr << ") in " << function << "(): " << std::endl
              << file << ":" << line << std::endl
              << "With message: " << msg << std::endl;

    std::abort();
}

} // namespace eul

#else

#define EUL_ASSERT_MSG(expr, msg) ((void)(0))

#endif // ASSERTION_ENABLED
