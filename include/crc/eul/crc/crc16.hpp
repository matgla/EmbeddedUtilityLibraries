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
 * @addtogroup crc16
 * @{
 */

using Crc16_CCITT_ZERO = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_XMODEM = Crc16_CCITT_ZERO;
using Crc16_ACORN = Crc16_XMODEM;
using Crc16_LTE = Crc16_XMODEM;
using Crc16_V_41_MSB = Crc16_XMODEM;

using Crc16_ARC = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16 = Crc16_ARC;
using Crc16_LHA = Crc16;
using Crc16_IBM = Crc16;

using Crc16_AUG_CCIT = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x1d0f>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_SPI_FUJITSU = Crc16_AUG_CCIT;

using Crc16_BUYPASS = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_UMTS = Crc16_BUYPASS;
using Crc16_VERIFONE = Crc16_BUYPASS;

using Crc16_CCIT_FALSE = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_AUTOSAR = Crc16_CCIT_FALSE;
using Crc16_IBM_3740 = Crc16_CCIT_FALSE;

using Crc16_CDMA2000 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0xc867>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_DDS_110 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x800d>()
    .set_xor_out<0x0000>()
    .build());


using Crc16_DECT_R = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x589>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0001>()
    .build());

using Crc16_DECT_X = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x589>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_DNP = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x3d65>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x0000>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_EN_13757 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x3d65>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_GENIBUS = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_DARC = Crc16_GENIBUS;
using Crc16_EPC = Crc16_GENIBUS;
using Crc16_EPC_C1G2 = Crc16_GENIBUS;
using Crc16_ICODE = Crc16_GENIBUS;


using Crc16_MAXIM = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x0000>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_MAXIM_DOW = Crc16_MAXIM;

using Crc16_MCRF4XX = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_RIELLO = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xb2aa>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_T10_DIF = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8bb7>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_TELEDISK = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0xa097>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_TMS37157 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x89ec>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_USB = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffff>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_A = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xc6c6>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_ISO_IEC_14443_3_A = Crc16_A;

using Crc16_KERMIT = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_CCITT = Crc16_KERMIT;
using Crc16_CCITT_TRUE = Crc16_KERMIT;
using Crc16_V_41_LSB = Crc16_KERMIT;

using Crc16_MODBUS = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_X_25 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffff>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_IBM_SDLC = Crc16_X_25;
using Crc16_ISO_HDLC = Crc16_X_25;
using Crc16_ISO_IEC_14443_3_B = Crc16_X_25;
using Crc16_B = Crc16_X_25;

using Crc16_CMS = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x8005>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_GSM = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1021>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_LJ1200 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x6f63>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_M17 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x5935>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_NRSC_5 = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x080b>()
    .set_refin<true>()
    .set_refout<true>()
    .set_init<0xffff>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_OPENSAFETY_A = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x5935>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_OPENSAFETY_B = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x755b>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0x0000>()
    .set_xor_out<0x0000>()
    .build());

using Crc16_PROFIBUS = decltype(CrcFactory<>{}
    .set_bits<16>()
    .set_type<uint16_t>() 
    .set_polynomial<0x1dcf>()
    .set_refin<false>()
    .set_refout<false>()
    .set_init<0xffff>()
    .set_xor_out<0xffff>()
    .build());

using Crc16_IEC_61158_2 = Crc16_PROFIBUS;

/** @} */

} // namespace eul::crc
