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
 * @addtogroup crc15
 * @{
 */

using Crc15_CAN = decltype(CrcFactory<>{}
    .set_bits<15>()
    .set_type<uint16_t>() 
    .set_polynomial<0x4599>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc15_MPT1327 = decltype(CrcFactory<>{}
    .set_bits<15>()
    .set_type<uint16_t>() 
    .set_polynomial<0x6815>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0001>()
    .build());

/** @} */

} // namespace eul::crc

