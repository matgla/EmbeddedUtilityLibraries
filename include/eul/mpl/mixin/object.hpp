#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/mixin/filter.hpp"
#include "eul/mpl/mixin/inherit_from.hpp"
#include "eul/mpl/mixin/interface.hpp"
#include "eul/mpl/mixin/type.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename... Types>
struct object
    : public inherit_from<
          typename filter<is_interface, Types<object<Types...>>...>::type>
{
public:
    using DataType = typename filter<is_data, Types<object<Types...>>...>::type;
    DataType data_;
    static_assert(std::tuple_size<DataType>::value != 0,
                  "Any data passed to mixed object.");
    static_assert(
        std::tuple_size<typename filter<
                is_interface, Types<object<Types...>>...>::type>::value
            != 0,
        "Any interface passed to mixed object.");


    friend class access<object>;
};

auto mix()
{
    return true;
}

} // namespace mixin
} // namespace mpl
} // namespace eul
