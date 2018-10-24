#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/mixin/interface.hpp"
#include "eul/mpl/mixin/filter.hpp"
#include "eul/mpl/mixin/inherit_from.hpp"
#include "eul/mpl/mixin/type.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename Interface, typename... Datas>
struct object : public inherit_from<object<Interface, Datas...>, Interface>
{
public:
    template <template <typename> typename... Interfaces>
    constexpr object(interface<Interfaces...>, Datas&&... args) : data_(std::forward<Datas>(args)...)
    {
    }

    using DataType = std::tuple<Datas...>;
    DataType data_;

    friend class access<object>;
};

template <template <typename> typename... Interfaces, typename... Datas>
object(interface<Interfaces...>, Datas...) -> object<interface<Interfaces...>::template type, Datas...>;

} // namespace mixin
} // namespace mpl
} // namespace eul
