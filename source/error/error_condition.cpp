#include "eul/error/error_condition.hpp"
#include "eul/error/generic_category.hpp"

namespace eul::error
{

error_condition::error_condition() noexcept
    : error_condition(0, generic_category())
{
}

error_condition::error_condition(int val, const error_category& cat) noexcept
    : value_(val)
    , category_(&cat)
{
}

void error_condition::assign(int val, const error_category& cat) noexcept
{
    value_ = val;
    category_ = &cat;
}

void error_condition::clear() noexcept
{
    value_ = 0;
}

int error_condition::value() const noexcept
{
    return value_;
}

const error_category& error_condition::category() const noexcept
{
    return *category_;
}

std::string_view error_condition::message() const
{
    return category_->message(value_);
}

error_condition::operator bool() const noexcept
{
    return value_ != 0;
}

bool error_condition::operator==(const error_condition& rhs) const noexcept
{
    return (*category_ == *rhs.category_) && value_ == rhs.value_;
}

} // namespace eul::error
