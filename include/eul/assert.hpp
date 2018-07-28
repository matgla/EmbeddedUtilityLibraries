#pragma once

#define EUL_ASSERT_MSG(expr, msg) ((expr) ? (void)0 : eul::assertFailed(#expr, __FILE__, __LINE__, __FUNCTION__, msg))

namespace eul
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
}

} // namespace eul