#pragma once

#include <string_view>

namespace eul::error
{

class error_category;
class error_condition;

template <typename ErrorConditionEnum>
error_condition make_error_condition(ErrorConditionEnum e);

class error_condition
{
public:
    error_condition() noexcept;
    ~error_condition() = default;

    error_condition(int val, const error_category& cat) noexcept;

    error_condition(const error_condition& other) noexcept;
    error_condition& operator=(const error_condition& other) noexcept;
    error_condition(error_condition&& other) noexcept = default;
    error_condition& operator=(error_condition&& other) noexcept = default;

    template <typename ErrorConditionEnum>
    error_condition(ErrorConditionEnum e) noexcept // NOLINT(google-explicit-constructor)
    {
        *this = make_error_condition(e);
    }


    template <typename ErrorConditionEnum>
    error_condition& operator=(ErrorConditionEnum e) noexcept
    {
        *this = make_error_condition(e);
        return *this;
    }

    void assign(int val, const error_category& cat) noexcept;

    void clear() noexcept;

    [[nodiscard]] int value() const noexcept;

    [[nodiscard]] const error_category& category() const noexcept;

    [[nodiscard]] std::string_view message() const;

    explicit operator bool() const noexcept;
    bool operator==(const error_condition& rhs) const noexcept;
    bool operator!=(const error_condition& rhs) const noexcept;
    bool operator<(const error_condition& rhs) const noexcept;
private:
    int value_{0};
    const error_category* category_{nullptr};
};

} // namespace eul::error
