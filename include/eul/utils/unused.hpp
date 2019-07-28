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

// clang-format on
