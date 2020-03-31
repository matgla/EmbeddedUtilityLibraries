#pragma once

#include <string_view>

namespace eul
{
namespace error
{

class error_condition;
class error_category;

class error_code;

template <typename ErrorCodeEnum>
error_code make_error_code(ErrorCodeEnum e);

class error_code
{
public:
    error_code() noexcept;

    error_code(int ec, const error_category& ecat) noexcept;

    template <typename ErrorCodeEnum>
    error_code(ErrorCodeEnum e) noexcept
    {
        *this = make_error_code(e);
    }

    template <typename ErrorCodeEnum>
    error_code& operator=(ErrorCodeEnum e) noexcept
    {
        *this = make_error_code(e);
        return *this;
    }

    void assign(int ec, const error_category& ecat) noexcept;

    int value() const noexcept;

    void clear() noexcept;

    const error_category& category() const noexcept;

    error_condition default_error_condition() const noexcept;

    std::string_view message() const;

    explicit operator bool() const noexcept;
    bool operator==(const error_code& rhs) const noexcept;
    bool operator!=(const error_code& rhs) const noexcept;
    bool operator<(const error_code& rhs) const noexcept;
private:
    const error_condition* condition_;
    const error_category* category_;
    int value_;
};

} // namespace error
} // namespace eul
