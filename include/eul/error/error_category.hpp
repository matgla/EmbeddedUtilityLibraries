#pragma once

#include <string_view>

namespace eul
{
namespace error
{

class error_condition;
class error_code;

class error_category
{
public:
    error_category(const error_category& other) = delete;
    constexpr error_category() noexcept
    {

    }

    virtual ~error_category() = default;

    error_category& operator=(const error_category& other) = delete;

    virtual std::string_view name() const noexcept = 0;
    virtual error_condition default_error_condition(int code) const noexcept;

    virtual bool equivalent(int code, const error_condition& condition) const noexcept;

    virtual bool equivalent(const error_code& code, int condition) const noexcept;

    virtual std::string_view message(int condition) const = 0;

    bool operator==(const error_category& rhs) const noexcept;
    bool operator!=(const error_category& rhs) const noexcept;
    bool operator<(const error_category& rhs) const noexcept;
};

} // namespace error
} // namespace eul
