#pragma once

#define EUL_ASSERT_MSG(expr, msg)                                              \
    ((expr) ? (void)0                                                          \
            : eul::assertFailed(#expr, __FILE__, __LINE__, __FUNCTION__, msg))

namespace eul
{

inline void assertFailed(const char* expr, const char* file, int line,
                         const char* function, const char* msg)
{
    static_cast<void>(expr);
    static_cast<void>(file);
    static_cast<void>(line);
    static_cast<void>(function);
    static_cast<void>(msg);
}

} // namespace eul