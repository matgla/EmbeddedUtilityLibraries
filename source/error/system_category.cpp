#include "eul/error/system_category.hpp"

namespace eul
{
namespace error
{

std::string_view system_category::name() const noexcept
{
    return "system";
}

std::string_view system_category::message(int condition) const
{
    switch (static_cast<errc>(condition))
    {
        case errc::argument_list_to_long: return "Argument list to big";
        case errc::permision_denied: return "Permission denied";
        default: return "Unknown error";
    }
}

system_category system_category_;

template <>
error_code make_error_code<errc>(errc e)
{
    return error_code(static_cast<int>(e), system_category_);
}

} // namespace error
} // namespace eul
