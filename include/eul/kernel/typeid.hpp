#pragma once

#include <cstddef>

namespace eul
{
namespace kernel
{

using typeid_t = std::size_t;

static typeid_t type_counter = 0;

template <typename T>
typeid_t type_id() noexcept
{
    static typeid_t const type_id = ++type_counter;
    return type_id;
}


} // namespace kernel
} // namespace eul
