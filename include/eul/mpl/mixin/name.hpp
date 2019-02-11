#pragma once

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename Name>
struct name
{
    using value = Name;
};

} // namespace mixin
} // namespace mpl
} // namespace eul
