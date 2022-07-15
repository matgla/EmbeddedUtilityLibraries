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

#pragma once 

#include "eul/crc/crc.hpp"

namespace eul::crc
{    
namespace detail 
{

/**
 * @ingroup crc
 * @brief Wraps type and contains information if it was set up
 * 
 * Needed to check if type setter was called on \ref CrcFactory
 * 
 * @tparam T holding type
 * @tparam was_initialized object initialization status
 */
template <typename T, bool was_initialized = false>
struct TemplateType
{
    using type = T;
    using self = TemplateType<T, was_initialized>;
    constexpr static inline bool initialized = was_initialized;
};

/**
 * @ingroup crc
 * @brief Unknown type for \ref TemplateType
 */
struct NoneType 
{};

constexpr NoneType none;

/**
 * @ingroup crc
 * @brief Wraps template value and contains information if it was set up
 * 
 * Needed to check if value setter was called on \ref CrcFactory
 * 
 * @tparam T value type
 * @tparam v holder for value
 * @tparam was_initialized object initialization status
 */
template <typename T, T v, bool was_initialized = false>
struct TemplateValue
{
    constexpr TemplateValue(NoneType) {};

    using type = T;
    using self = TemplateValue<T, v, was_initialized>;
    constexpr static inline T value = v;
    constexpr static inline bool initialized = was_initialized;
};

} // namespace detail

/**
 * @ingroup crc
 * @brief Factory class to easily configure \ref Crc algorithm class
 * 
 * Parameters for template class are filled by creation methods. Not needed to know what are they really do.
 */

template <typename T = detail::TemplateType<int>, 
    typename polynomial = detail::TemplateValue<typename T::type, 0, false>, 
    typename xor_out = detail::TemplateValue<typename T::type, 0, false>, 
    typename init = detail::TemplateValue<typename T::type, 0, false>, 
    typename refin = detail::TemplateValue<bool, false, false>, 
    typename refout = detail::TemplateValue<bool, false, false>, 
    typename bits = detail::TemplateValue<uint8_t, 0, false>>
class CrcFactory
{
public:

    /**
     * @brief Set the CRC register type
     * 
     * @tparam DataType CRC register type
     * @return \ref CrcFactory type with filled CRC register type
     */
    template <typename DataType>
    constexpr static auto set_type()
    {
        return CrcFactory<detail::TemplateType<DataType, true>, polynomial, xor_out, init, refin, refout, bits>{};
    }

    /**
     * @brief Set the polynomial value
     * 
     * @tparam polynomial_value value of polynomial
     * @return \ref CrcFactory type with filled polynomial
     */
    template <typename T::type polynomial_value>
    constexpr static auto set_polynomial() 
    {
        static_assert(T::initialized, "The type must be set before changing the polynomial");
        return CrcFactory<T, detail::TemplateValue<typename T::type, polynomial_value, true>, xor_out, init, refin, refout, bits>{};
    }

    /**
     * @brief Set the output xor value
     * 
     * @tparam xor_out_value value for xor operation
     * @return \ref CrcFactory type with filled xor value
     */
    template <typename T::type xor_out_value>
    constexpr static auto set_xor_out() 
    {
        static_assert(T::initialized, "The type must be set before changing the value for xor output");
        return CrcFactory<T, polynomial, detail::TemplateValue<typename T::type, xor_out_value, true>, init, refin, refout, bits>{};
    }

    /**
     * @brief Set the initial CRC register value
     * 
     * @tparam init_value value for CRC register initialization
     * @return \ref CrcFactory type with initialization value
     */
    template <typename T::type init_value>
    constexpr static auto set_init() 
    {
        static_assert(T::initialized, "The type must be set before changing the intialization value");
        return CrcFactory<T, polynomial, xor_out, detail::TemplateValue<typename T::type, init_value, true>, refin, refout, bits>{};
    }

    /**
     * @brief Set the input reflection
     * 
     * @tparam refin_value toggles input data reflection
     * @return \ref CrcFactory type with filled input reflection flag
     */
    template <bool refin_value>
    constexpr static auto set_refin() 
    {
        return CrcFactory<T, polynomial, xor_out, init, detail::TemplateValue<bool, refin_value, true>, refout, bits>{};
    }

    /**
     * @brief Set the output reflection
     * 
     * @tparam refin_value toggles output CRC value reflection
     * @return \ref CrcFactory type with filled output reflection flag
     */
    template <bool refout_value>
    constexpr static auto set_refout() 
    {
        return CrcFactory<T, polynomial, xor_out, init, refin, detail::TemplateValue<bool, refout_value, true>, bits>{};
    }

    /**
     * @brief Set the number of the CRC register bit size 
     * 
     * @tparam bits_value number of CRC register bit size
     * @return \ref CrcFactory type with filled CRC register size 
     */
    template <uint8_t bits_value>
    constexpr static auto set_bits() 
    {
        return CrcFactory<T, polynomial, xor_out, init, refin, refout, detail::TemplateValue<uint8_t, bits_value, true>>{};
    }

    /**
     * @brief Construct \ref Crc object
     * 
     * Used to construct CRC object with specified configuration.
     * 
     * @return \ref Crc object with given configuration
     */
    constexpr static auto build() 
    {
        static_assert(T::initialized, "non-initialized type");
        static_assert(polynomial::initialized, "non-initialized polynomial");
        static_assert(xor_out::initialized, "non-initialized xor_out");
        static_assert(init::initialized, "non-initialized init value");
        static_assert(refin::initialized, "non-initialized refin");
        static_assert(refout::initialized, "non-initialized refout");
        static_assert(bits::initialized, "non-initialized bits");
        return Crc<typename T::type, polynomial::value, xor_out::value, init::value, 
            refin::value, refout::value, bits::value>();
    }

};

} // namespace eul::crc
