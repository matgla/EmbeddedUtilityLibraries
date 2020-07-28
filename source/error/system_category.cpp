#include "eul/error/system_category.hpp"

namespace eul::error
{

class system_category_impl : public error_category
{
public:
    static const system_category_impl& get()
    {
        static system_category_impl impl;
        return impl;
    }
    [[nodiscard]] std::string_view name() const noexcept override;
    [[nodiscard]] std::string_view message(int condition) const override;
};

std::string_view system_category_impl::name() const noexcept
{
    return "system";
}

std::string_view system_category_impl::message(int condition) const
{
    switch (static_cast<errc>(condition))
    {
        case errc::argument_list_to_long: return "Argument list to big";
        case errc::permission_denied: return "Permission denied";
        default: return "Unknown error";
    }
}

template <>
error_code make_error_code<errc>(errc e)
{
    return error_code(static_cast<int>(e), system_category_impl::get());
}

const error_category& system_category() noexcept
{
    return system_category_impl::get();
}

} // namespace eul::error
