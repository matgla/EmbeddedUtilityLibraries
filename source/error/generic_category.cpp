#include "eul/error/generic_category.hpp"

#include "eul/utils/unused.hpp"

namespace eul::error
{

class generic_category_impl : public error_category
{
public:
    [[nodiscard]] std::string_view name() const noexcept override;
    [[nodiscard]] std::string_view message(int condition) const override;
};

std::string_view generic_category_impl::name() const noexcept
{
    return "generic";
}

std::string_view generic_category_impl::message(int condition) const
{
    UNUSED1(condition);
    return "generic";
}

const error_category& generic_category() noexcept
{
    static generic_category_impl impl{};
    return impl;
}

} // namespace eul::error
