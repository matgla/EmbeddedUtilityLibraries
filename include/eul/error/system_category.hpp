#pragma once

#include "eul/error/error_category.hpp"

#include "eul/error/error_code.hpp"

namespace eul::error
{

enum class errc
{
    argument_list_to_long = 1,
    permission_denied = 2,
};

template <>
error_code make_error_code<errc>(errc e);

const error_category& system_category() noexcept;

} // namespace eul::error
