#include "eul/error/error_category.hpp"

#include "eul/error/error_code.hpp"

namespace eul
{
namespace error
{

enum class errc
{
    argument_list_to_long = 1,
    permision_denied
};

template <>
error_code make_error_code<errc>(errc e);

class system_category : public error_category
{
public:
    std::string_view name() const noexcept override;
    std::string_view message(int condition) const override;
};

} // namespace error
} // namespace eul
