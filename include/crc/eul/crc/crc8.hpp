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
 * @addtogroup crc8
 * @{
 */

using Crc8 = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x07>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_SMBUS = Crc8;

using Crc8_SAE_J1850 = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xff>()
    .set_xor_out<0xff>()
    .build());

using Crc8_SAE_J1850_ZERO = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_8H2F = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x2f>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xff>()
    .set_xor_out<0xff>()
    .build());

using Crc8_CDMA2000 = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x9b>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xff>()
    .set_xor_out<0x00>()
    .build());

using Crc8_DARC = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x39>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_DVB_S2 = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0xd5>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_EBU = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xff>()
    .set_xor_out<0x00>()
    .build());

using Crc8_ICODE = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xfd>()
    .set_xor_out<0x00>()
    .build());

using Crc8_ITU = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x07>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x55>()
    .build());

using Crc8_MAXIM = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x31>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_ROHC = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x07>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xff>()
    .set_xor_out<0x00>()
    .build());

using Crc8_WCDMA = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x9b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_GSM_A = Crc8_SAE_J1850_ZERO;
using Crc8_GSM_B = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x49>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0xff>()
    .build());

using Crc8_AUTOSAR = Crc8_8H2F;

using Crc8_TECH_3250 = Crc8_EBU;
using Crc8_AES = Crc8_EBU;
using Crc8_I_432_1 = Crc8_ITU;

using Crc8_MAXIM_DOW = Crc8_MAXIM;
using Crc8_DOW = Crc8_MAXIM;


using Crc8_BLUETOOTH = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0xa7>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_HITAG = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xff>()
    .set_xor_out<0x00>()
    .build());

using Crc8_LTE = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x9b>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

using Crc8_MIFARE_MAD = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x1d>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xc7>()
    .set_xor_out<0x00>()
    .build());

using Crc8_NRSC_5 = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x31>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xff>()
    .set_xor_out<0x00>()
    .build());

using Crc8_OPENSAFETY = decltype(CrcFactory<>{}
    .set_bits<8>()
    .set_type<uint8_t>() 
    .set_polynomial<0x2f>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x00>()
    .set_xor_out<0x00>()
    .build());

/** @} */

} // namespace eul::crc

