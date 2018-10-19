#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/mixin/base.hpp"
#include "eul/mpl/mixin/filter.hpp"
#include "eul/mpl/mixin/inherit_from.hpp"
#include "eul/mpl/mixin/type.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename Base, typename... Datas>
struct object : public inherit_from<object<Base, Datas...>, Base>
{
public:
    template <typename... Args>
    object(Args&&... args) : data_(std::forward<Args>(args)...)
    {
    }

    using DataType = std::tuple<Datas...>;
    DataType data_;

    friend class access<object>;
};

template <template <typename> typename Base>
struct compose
{
    template <typename... Args>
    constexpr static object<Base, Args...> with_data(Args&&... args)
    {
        return object<Base, Args...>(std::forward<Args>(args)...);
    }
};

} // namespace mixin
} // namespace mpl
} // namespace eul
