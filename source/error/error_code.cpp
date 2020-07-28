#include "eul/error/error_code.hpp"

#include "eul/error/system_category.hpp"

#include "eul/error/error_category.hpp"
#include "eul/error/error_condition.hpp"

namespace eul::error
{

error_code::error_code() noexcept
    : error_code(0, system_category())
{
}

error_code::error_code(int ec, const error_category& ecat) noexcept
    : condition_(nullptr)
    , category_(&ecat)
    , value_(ec)


{
}

void error_code::assign(int ec, const error_category& ecat) noexcept
{
    value_ = ec;
    category_ = &ecat;
}

int error_code::value() const noexcept
{
    return value_;
}

void error_code::clear() noexcept
{
    value_ = 0;
}

const error_category& error_code::category() const noexcept
{
    return *category_;
}

error_condition error_code::default_error_condition() const noexcept
{
    return *condition_;
}

std::string_view error_code::message() const
{
    return category_->message(value_);
}

error_code::operator bool() const noexcept
{
    return value_ != 0;
}

bool error_code::operator==(const error_code& rhs) const noexcept
{
    return (*category_ == *rhs.category_) && value_ == rhs.value_;
}

bool error_code::operator!=(const error_code& rhs) const noexcept
{
    return !operator==(rhs);
}

bool error_code::operator<(const error_code& rhs) const noexcept
{
    return (*this->category_ < *rhs.category_)
        || ((*this->category_ == *rhs.category_) && value_ < rhs.value_);
}

} // namespace eul::error
