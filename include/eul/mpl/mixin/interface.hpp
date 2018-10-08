#pragma once

#include <tuple>
#include <type_traits>

namespace eul
{
namespace mpl
{
namespace mixin
{

template <typename T>
struct interface_t : public T
{
};

template <template <typename> typename Ts>
struct interface
{
    template <typename T>
    using type = interface_t<Ts<T>>;
};

template <typename T>
struct is_interface : std::false_type
{
};

template <typename T>
struct is_interface<interface_t<T>> : std::true_type
{
};

template <typename T>
struct data_t : public T
{
    using type = T;
};

template <typename T>
struct data
{
    template <typename MixinType>
    using type = data_t<T>;
};

template <typename T>
struct is_data : std::false_type
{
};

template <typename T>
struct is_data<data_t<T>> : std::true_type
{
};

} // namespace mixin
} // namespace mpl
} // namespace eul
