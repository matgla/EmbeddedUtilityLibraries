// This file is part of EmbeddedUtilityLibraries project.
// Copyright (C) 2022 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/* based on catalogue from: https://reveng.sourceforge.io/crc-catalogue/ */

#pragma once 

#include <cstdint>
 
#include "eul/crc/crc_factory.hpp"

namespace eul::crc 
{

/**
 * @addtogroup crc32
 * @{
 */

using Crc32 = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x04c11db7>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_ADCCP = Crc32;
using Crc32_ISO_HDLC = Crc32;
using Crc32_V42 = Crc32;
using Crc32_XZ = Crc32;

using Crc32_BZIP = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x04c11db7>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffffffff>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_AAL5 = Crc32_BZIP;
using Crc32_DECT_B = Crc32_BZIP;

using Crc32_C = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x1edc6f41>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_BASE91_C = Crc32_C;
using Crc32_CASTAGNOLI = Crc32_C;
using Crc32_INTERLAKEN = Crc32_C;

using Crc32_D = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0xa833982b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_BASE91_D = Crc32_D;

using Crc32_MPEG2 = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x04c11db7>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffffffff>()
    .set_xor_out<0x00000000>()
    .build());

using Crc32_POSIX = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x04c11db7>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00000000>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_CKSUM = Crc32_POSIX;

using Crc32_Q = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x814141ab>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00000000>()
    .set_xor_out<0x00000000>()
    .build());

using Crc32_AXIM = Crc32_Q;


using Crc32_JAMCRC = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x04c11db7>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0x00000000>()
    .build());

using Crc32_XFER = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x000000af>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00000000>()
    .set_xor_out<0x00000000>()
    .build());

using Crc32_AUTOSAR = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0xf4acfb13>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0xffffffff>()
    .build());

using Crc32_CD_ROM_EDC = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x8001801b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00000000>()
    .set_xor_out<0x00000000>()
    .build());

using Crc32_MEF = decltype(CrcFactory<>{}
    .set_bits<32>()
    .set_type<uint32_t>() 
    .set_polynomial<0x741b8cd7>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffff>()
    .set_xor_out<0x00000000>()
    .build());

/** @} */

} // namespace eul::crc
