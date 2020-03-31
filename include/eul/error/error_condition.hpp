#pragma once

#include <string_view>

namespace eul
{
namespace error
{

class error_category;

class error_condition
{
public:
    error_condition() noexcept;
    error_condition(const error_condition& other) noexcept;
    error_condition(int val, const error_category& cat) noexcept;

    template <typename ErrorConditionEnum>
    error_condition(ErrorConditionEnum e) noexcept
    {

    }

    error_condition& operator=(const error_condition& other) noexcept;

    template <typename ErrorConditionEnum>
    error_condition& operator=(ErrorConditionEnum e) noexcept
    {
        return *this;
    }

    void assign(int val, const error_category& cat) noexcept;

    void clear() noexcept;

    int value() const noexcept;

    const error_category& category() const noexcept;

    std::string_view message() const;

    explicit operator bool() const noexcept;
    bool operator==(const error_condition& rhs) const noexcept;
    bool operator!=(const error_condition& rhs) const noexcept;
    bool operator<(const error_condition& rhs) const noexcept;
private:
    error_category* error_category_;
};

} // namespace error
} // namespace eul
