CRC library {#crc_page}
=======================

Library for CRC computing. It's highly configurable with a design that allows adding new algorithms quickly. 
There are a lot of configurations provided by the library. 

Code is under `eul/crc/*`. 

Adding own algorithm
====================

The simplest way to add your own CRC definition is to use @ref eul::crc::CrcFactory. 

```cpp

#include <cstdint>

#include <eul/crc/crc_factory.hpp>

using MyAwesomeCrcAlgorithm = decltype(CrcFactory<>{}
    .set_bits<19>()
    .set_type<uint32_t>() 
    .set_polynomial<0x0abc>()
    .set_refin<true>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0xffff>()
    .build());

```

For more examples, look to algorithms definitions inside `eul/crc/crc*.hpp` (@ref crc)

Usage example
=============

CMakeLists.txt
--------------

@snippet crc/crc/CMakeLists.txt Doxygen CRC example - CMake

crc_usage.cpp
-------------

@snippet crc/crc/crc_usage.cpp Doxygen CRC example - source

@defgroup crc "CRC"
@{
@defgroup crc3 "Crc3 algorithms"
@ingroup crc
@defgroup crc4 "Crc4 algorithms"
@ingroup crc
@defgroup crc5 "Crc5 algorithms"
@ingroup crc
@defgroup crc6 "Crc6 algorithms"
@ingroup crc
@defgroup crc7 "Crc7 algorithms"
@ingroup crc
@defgroup crc8 "Crc8 algorithms"
@ingroup crc
@defgroup crc10 "Crc10 algorithms"
@ingroup crc
@defgroup crc11 "Crc11 algorithms"
@ingroup crc
@defgroup crc12 "Crc12 algorithms"
@ingroup crc
@defgroup crc13 "Crc13 algorithms"
@ingroup crc
@defgroup crc14 "Crc14 algorithms"
@ingroup crc
@defgroup crc15 "Crc15 algorithms"
@ingroup crc
@defgroup crc16 "Crc16 algorithms"
@ingroup crc
@defgroup crc17 "Crc17 algorithms"
@ingroup crc
@defgroup crc21 "Crc21 algorithms"
@ingroup crc
@defgroup crc24 "Crc24 algorithms"
@ingroup crc
@defgroup crc30 "Crc30 algorithms"
@ingroup crc
@defgroup crc31 "Crc31 algorithms"
@ingroup crc
@defgroup crc32 "Crc32 algorithms"
@ingroup crc
@defgroup crc40 "Crc40 algorithms"
@ingroup crc
@defgroup crc64 "Crc64 algorithms"
@ingroup crc
@}