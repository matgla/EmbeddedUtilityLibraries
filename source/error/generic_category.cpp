#include "eul/error/generic_category.hpp"

namespace eul
{
namespace error
{

class generic_category_impl : public error_category
{
public:
    std::string_view name() const noexcept override;
    std::string_view message(int condition) const override;
};

std::string_view generic_category_impl::name() const noexcept
{
    return "generic";
}

std::string_view generic_category_impl::message(int condition) const
{
    return "generic";
}

generic_category_impl generic_category_;

const error_category& generic_category() noexcept
{
    return generic_category_;
}

} // namespace error
} // namespace eul
