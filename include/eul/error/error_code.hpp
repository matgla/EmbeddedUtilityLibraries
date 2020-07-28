#pragma once

#include <string_view>

namespace eul::error
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
    error_code(ErrorCodeEnum e) noexcept // NOLINT(google-explicit-constructor, cppcoreguidelines-pro-type-member-init)
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

    [[nodiscard]] int value() const noexcept;

    void clear() noexcept;

    [[nodiscard]] const error_category& category() const noexcept;

    [[nodiscard]] error_condition default_error_condition() const noexcept;

    [[nodiscard]] std::string_view message() const;

    explicit operator bool() const noexcept;
    bool operator==(const error_code& rhs) const noexcept;
    bool operator!=(const error_code& rhs) const noexcept;
    bool operator<(const error_code& rhs) const noexcept;
private:
    const error_condition* condition_;
    const error_category* category_;
    int value_{-1};
};

} // namespace eul::error
