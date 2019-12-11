// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
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

#include <string_view>

#include <gsl/span>

#include "eul/time/fwd.hpp"

namespace eul
{
namespace logger
{


struct logging_flags
{
public:
    enum class base : uint8_t
    {
        dec,
        hex,
        oct,
        bin
    };

    enum class boolalpha : uint8_t
    {
        enabled,
        disabled
    };

    logging_flags()
        : base_(base::dec)
        , boolalpha_(boolalpha::disabled)
    {
    }

    void set_base(const base new_base)
    {
        base_ = new_base;
    }

    base get_base() const
    {
        return base_;
    }

    void set_boolalpha(const boolalpha new_boolalpha)
    {
        boolalpha_ = new_boolalpha;
    }

    boolalpha get_boolalpha() const
    {
        return boolalpha_;
    }

private:
    base base_;
    boolalpha boolalpha_;
};

constexpr logging_flags::base dec = logging_flags::base::dec;
constexpr logging_flags::base hex = logging_flags::base::hex;
constexpr logging_flags::base oct = logging_flags::base::oct;
constexpr logging_flags::base bin = logging_flags::base::bin;

constexpr logging_flags::boolalpha boolalpha = logging_flags::boolalpha::enabled;

class logger_printer final
{
public:
    logger_printer(
        const std::string_view& prefix,
        const std::string_view& name,
        const std::string_view& user_prefix,
        const time::i_time_provider& time);

    logger_printer(
        const std::string_view& prefix,
        const std::string_view& name,
        const time::i_time_provider& time);
    ~logger_printer();

    logger_printer& operator<<(const std::string_view& str);

    logger_printer& operator<<(const logging_flags::base base)
    {
        flags_.set_base(base);
        return *this;
    }

    logger_printer& operator<<(const logging_flags::boolalpha boolalpha)
    {
        flags_.set_boolalpha(boolalpha);
        return *this;
    }

    template<typename T>
    logger_printer& operator<<(const gsl::span<T>& data)
    {
        write_to_streams("{");
        if (!data.empty())
        {
            for (typename gsl::span<T>::index_type i = 0; i < data.size() - 1; ++i)
            {
                *this << data[i] << ", ";
            }
            *this << data[data.size() - 1] << "}";
        }
        else
        {
            *this << "}";
        }
        return *this;
    }

    template <typename T,
        typename std::enable_if_t<std::is_same_v<T, bool>, int> = 0>
    logger_printer& operator<<(const T data)
    {
        if (flags_.get_boolalpha() == logging_flags::boolalpha::enabled)
        {
            if (data == 0)
            {
                write_to_streams("false");
                return *this;
            }
            else if (data == 1)
            {
                write_to_streams("true");
                return *this;
            }
        }
        return (*this << static_cast<int>(data));
    }

    template <typename T, typename std::enable_if_t<
        std::conjunction_v<std::is_integral<T>, std::is_signed<T>, std::negation<std::is_same<T, bool>>>, int
    > = 0>
    logger_printer& operator<<(T data)
    {
        int base = get_base();

        if (data < 0)
        {
            char digit[1] = {'-'};
            write_to_streams(digit);
            data *= -1;
        }

        int zeros_at_end = reverse_number(data, base);
        write_number_as_text(data, base, zeros_at_end);
        return *this;
    }

    template <typename T, typename std::enable_if_t<
        std::conjunction_v<std::is_integral<T>, std::is_unsigned<T>, std::negation<std::is_same<T, bool>>>, int
    > = 0>
    logger_printer& operator<<(T data)
    {
        int base = get_base();

        int zeros_at_end = reverse_number(data, base);
        write_number_as_text(data, base, zeros_at_end);

        return *this;
    }

protected:

    int get_base() const;

    void printHeader(std::string_view level) const;
    void printHeader(std::string_view level, std::string_view user_prefix) const;
    void printTimeAndDate() const;
    void write_to_streams(const std::string_view& data) const;


    template <typename T>
    int reverse_number(T& number, int base)
    {
        if (number == 0)
        {
            return 1;
        }

        T data = number;

        number = 0;
        int zeros_at_end = 0;
        bool is_zero_at_end = true;

        while (data != 0)
        {
            int temp = data % base;
            if (is_zero_at_end && temp == 0)
            {
                ++zeros_at_end;
            }
            else
            {
                is_zero_at_end = false;
            }
            number = number * base + temp;
            data /= base;
        }
        return zeros_at_end;
    }

    template <typename T>
    void write_number_as_text(T number, int base, int zeros_at_end)
    {
        while (number != 0)
        {
            char digit[2];
            digit[0] = {"0123456789abcdef"[number%base]};
            digit[1] = 0;
            write_to_streams(digit);
            number /= base;
        }
        while (zeros_at_end)
        {
            char digit[2];
            digit[0] = {'0'};
            digit[1] = 0;
            write_to_streams(digit);
            --zeros_at_end;
        }
    }


    const std::string_view name_;
    const time::i_time_provider& time_;
    logging_flags flags_;
};

} // namespace logger
} // namespace eul
