#pragma once

#include <tuple>

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename MixinType, template <typename> typename... Types>
struct inherit_from : public Types<MixinType>...
{
};

template <typename... T>
struct inherit_from<std::tuple<T...>> : public T...
{
};

} // namespace mixin
} // namespace mpl
} // namespace eul
