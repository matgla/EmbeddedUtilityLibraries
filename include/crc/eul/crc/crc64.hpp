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
 * @addtogroup crc64
 * @{
 */

using Crc64_ECMA_182 = decltype(CrcFactory<>{}
    .set_bits<64>()
    .set_type<uint64_t>() 
    .set_polynomial<0x42f0e1eba9ea3693>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000000000000000>()
    .set_xor_out<0x0000000000000000>()
    .build());

using Crc64 = Crc64_ECMA_182;

using Crc64_GO_ISO = decltype(CrcFactory<>{}
    .set_bits<64>()
    .set_type<uint64_t>() 
    .set_polynomial<0x000000000000001b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffffffffffff>()
    .set_xor_out<0xffffffffffffffff>()
    .build());

using Crc64_WE = decltype(CrcFactory<>{}
    .set_bits<64>()
    .set_type<uint64_t>() 
    .set_polynomial<0x42f0e1eba9ea3693>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffffffffffffffff>()
    .set_xor_out<0xffffffffffffffff>()
    .build());

using Crc64_XZ = decltype(CrcFactory<>{}
    .set_bits<64>()
    .set_type<uint64_t>() 
    .set_polynomial<0x42f0e1eba9ea3693>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffffffffffff>()
    .set_xor_out<0xffffffffffffffff>()
    .build());

using Crc64_MS = decltype(CrcFactory<>{}
    .set_bits<64>()
    .set_type<uint64_t>() 
    .set_polynomial<0x259c84cba6426349>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffffffffffffffff>()
    .set_xor_out<0x0000000000000000>()
    .build());

/** @} */

} // namespace eul::crc
