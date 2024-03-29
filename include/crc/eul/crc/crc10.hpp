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
 * @addtogroup crc10
 * @{
 */

using Crc10_ATM = decltype(CrcFactory<>{}
    .set_bits<10>()
    .set_type<uint16_t>() 
    .set_polynomial<0x233>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x000>()
    .set_xor_out<0x000>()
    .build());

using Crc10 = Crc10_ATM;
using Crc10_I_610 = Crc10_ATM;

using Crc10_CDMA2000 = decltype(CrcFactory<>{}
    .set_bits<10>()
    .set_type<uint16_t>() 
    .set_polynomial<0x3d9>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x3ff>()
    .set_xor_out<0x000>()
    .build());

using Crc10_GSM = decltype(CrcFactory<>{}
    .set_bits<10>()
    .set_type<uint16_t>() 
    .set_polynomial<0x175>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x000>()
    .set_xor_out<0x3ff>()
    .build());

/** @} */

} // namespace eul::crc

