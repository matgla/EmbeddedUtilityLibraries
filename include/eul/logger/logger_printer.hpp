#pragma once

#include <string_view>

#include <gsl/span>

#include "eul/time/fwd.hpp"

namespace eul
{
namespace logger
{

class logger_printer final
{
public:
    logger_printer(
        const std::string_view& prefix,
        const std::string_view& name,
        const time::i_time_provider& time);
    ~logger_printer();

    const logger_printer& operator<<(const std::string_view& str) const;

    template<typename T>
    const logger_printer& operator<<(const gsl::span<T>& data) const
    {
        write_to_streams("{");
        for (typename gsl::span<T>::index_type i = 0; i < data.size() - 1; ++i)
        {
            *this << static_cast<int>(data[i]) << ", ";
        }
        *this << static_cast<int>(data[data.size() - 1]) << "}";
        return *this;
    }

    const logger_printer& operator<<(int data) const;
protected:

    void printHeader(std::string_view level) const;
    void printTimeAndDate() const;
    void write_to_streams(const std::string_view& data) const;

    const std::string_view name_;
    const time::i_time_provider& time_;
};

} // namespace logger
} // namespace eul
