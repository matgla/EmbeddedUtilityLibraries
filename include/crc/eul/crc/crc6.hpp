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
 * @addtogroup crc6
 * @{
 */

using Crc6_CDMA2000_A = decltype(CrcFactory<>{}
    .set_bits<6>()
    .set_type<uint8_t>() 
    .set_polynomial<0x27>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x3f>()
    .set_xor_out<0x00>()
    .build());

using Crc6_CDMA2000_B = decltype(CrcFactory<>{}
    .set_bits<6>()
    .set_type<uint8_t>() 
    .set_polynomial<0x07>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x3f>()
    .set_xor_out<0x00>()
    .build());

using Crc6_DARC = decltype(CrcFactory<>{}
    .set_bits<6>()
    .set_type<uint8_t>() 
    .set_polynomial<0x19>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc6_G_704 = decltype(CrcFactory<>{}
    .set_bits<6>()
    .set_type<uint8_t>() 
    .set_polynomial<0x03>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc6_ITU = Crc6_G_704;

using Crc6_GSM = decltype(CrcFactory<>{}
    .set_bits<6>()
    .set_type<uint8_t>() 
    .set_polynomial<0x2f>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x3f>()
    .build());

/** @} */

} // namespace eul::crc

