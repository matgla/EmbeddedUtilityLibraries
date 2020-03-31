#include "eul/error/error_category.hpp"

#include <functional>

#include "eul/error/error_condition.hpp"
#include "eul/error/error_code.hpp"

namespace eul
{
namespace error
{

error_condition error_category::default_error_condition(int code) const noexcept
{
    return error_condition(code, *this);
}

bool error_category::equivalent(int code, const error_condition& condition) const noexcept
{
    return default_error_condition(code) == condition;
}

bool error_category::equivalent(const error_code& code, int condition) const noexcept
{
    return *this == code.category() && code.value() == condition;
}

bool error_category::operator==(const error_category& rhs) const noexcept
{
    return this == &rhs;
}

bool error_category::operator!=(const error_category& rhs) const noexcept
{
    return this != &rhs;
}

bool error_category::operator<(const error_category& rhs) const noexcept
{
    return std::less<const error_category*>()(this, &rhs);
}

} // namespace error
} // namespace eul
