#pragma once

// clang-format off
#define UNUSED1(x) (void)(x)

#define UNUSED2(x, y) \
    UNUSED1(x);       \
    UNUSED1(y)

#define UNUSED3(x, y, z) \
    UNUSED2(y, z);       \
    UNUSED1(x)

#define UNUSED4(x, y, z, e) \
    UNUSED3(y, z, e);       \
    UNUSED1(x)

#define UNUSED5(x, y, z, e, f) \
    UNUSED4(y, z, e, f);       \
    UNUSED1(x)

#define UNUSED6(x, y, z, e, f, g) \
    UNUSED5(y, z, e, f, g);       \
    UNUSED1(x)

#define UNUSED7(x, y, z, e, f, g, h) \
    UNUSED6(y, z, e, f, g, h);       \
    UNUSED1(x)

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1)

#define ALL_UNUSED_IMPL_(nargs) UNUSED##nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define UNUSED(...) ALL_UNUSED_IMPL(VA_NUM_ARGS(__VA_ARGS__)) (__VA_ARGS__)
// clang-format on
