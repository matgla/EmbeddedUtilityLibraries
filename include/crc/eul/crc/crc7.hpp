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
 * @addtogroup crc7
 * @{
 */

using Crc7_MMC = decltype(CrcFactory<>{}
    .set_bits<7>()
    .set_type<uint8_t>() 
    .set_polynomial<0x09>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc7 = Crc7_MMC;

using Crc7_ROHC = decltype(CrcFactory<>{}
    .set_bits<7>()
    .set_type<uint8_t>() 
    .set_polynomial<0x4f>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x7f>()
    .set_xor_out<0x00>()
    .build());

using Crc7_UMTS = decltype(CrcFactory<>{}
    .set_bits<7>()
    .set_type<uint8_t>() 
    .set_polynomial<0x45>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

/** @} */

} // namespace eul::crc

