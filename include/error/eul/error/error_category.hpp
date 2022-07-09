#pragma once

#include <compare>
#include <string_view>

namespace eul::error
{

class error_condition;
class error_code;

class error_category
{
public:
    constexpr error_category() noexcept = default;
    virtual ~error_category() = default;

    error_category(const error_category& other) = delete;
    error_category& operator=(const error_category& other) = delete;

    error_category(error_category&& other) = default;
    error_category& operator=(error_category&& other) = default;


    [[nodiscard]]
    virtual std::string_view name() const noexcept = 0;

    [[nodiscard]]
    virtual error_condition default_error_condition(int code) const noexcept;

    [[nodiscard]]
    virtual bool equivalent(int code, const error_condition& condition) const noexcept;

    [[nodiscard]]
    virtual bool equivalent(const error_code& code, int condition) const noexcept;

    [[nodiscard]]
    virtual std::string_view message(int condition) const = 0;

    bool operator==(const error_category& rhs) const noexcept;
    auto operator<=>(const error_category& rhs) const noexcept
    {
        return std::compare_three_way()(this, &rhs);
    }
};

} // namespace eul::error
