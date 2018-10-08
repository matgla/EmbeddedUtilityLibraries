#pragma once

#include <tuple>

namespace eul
{
namespace mpl
{

template <typename MixinType, template <typename> typename... Types>
struct inherit_from : public Types<MixinType>...
{
};

template <typename... T>
struct inherit_from<std::tuple<T...>> : public T...
{
};

} // namespace mpl
} // namespace eul
