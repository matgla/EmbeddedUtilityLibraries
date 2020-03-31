#include "eul/error/error_condition.hpp"

namespace eul
{
namespace error
{

error_condition::error_condition() noexcept
{

}

error_condition::error_condition(const error_condition& other) noexcept
{

}
error_condition::error_condition(int val, const error_category& cat) noexcept
{

}

error_condition& error_condition::operator=(const error_condition& other) noexcept
{
    return *this;
}

void error_condition::assign(int val, const error_category& cat) noexcept
{

}

void error_condition::clear() noexcept
{

}

int error_condition::value() const noexcept
{
    return 0;
}

const error_category& error_condition::category() const noexcept
{
    return *error_category_;
}

std::string_view error_condition::message() const
{
    return "";
}

error_condition::operator bool() const noexcept
{
    return true;
}

bool error_condition::operator==(const error_condition& rhs) const noexcept
{
    return true;
}

bool error_condition::operator!=(const error_condition& rhs) const noexcept
{
    return true;
}

bool error_condition::operator<(const error_condition& rhs) const noexcept
{
    return true;
}

} // namespace error
} // namespace eul
