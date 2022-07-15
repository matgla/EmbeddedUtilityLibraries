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
 * @addtogroup crc24
 * @{
 */

using Crc24_BLE = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x00065b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x555555>()
    .set_xor_out<0x000000>()
    .build());

using Crc24_FLEXRAY_A = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x5d6dcb>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xfedcba>()
    .set_xor_out<0x000000>()
    .build());

using Crc24_FLEXRAY_B = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x5d6dcb>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xabcdef>()
    .set_xor_out<0x000000>()
    .build());

using Crc24_INTERLAKEN = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x328b63>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffffff>()
    .set_xor_out<0xffffff>()
    .build());

using Crc24_LTE_A = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x864cfb>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x000000>()
    .set_xor_out<0x000000>()
    .build());

using Crc24_LTE_B = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x800063>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x000000>()
    .set_xor_out<0x000000>()
    .build());

using Crc24_OPENPGP = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x864cfb>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xb704ce>()
    .set_xor_out<0x000000>()
    .build());

using Crc24 = Crc24_OPENPGP;

using Crc24_OS_9 = decltype(CrcFactory<>{}
    .set_bits<24>()
    .set_type<uint32_t>() 
    .set_polynomial<0x800063>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffffff>()
    .set_xor_out<0xffffff>()
    .build());

/** @} */

} // namespace eul::crc

