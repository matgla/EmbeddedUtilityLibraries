#pragma once

#include <tuple>
#include <type_traits>

#include "eul/mpl/filter.hpp"
#include "eul/mpl/inherit_from.hpp"
#include "eul/mpl/mixin/interface.hpp"

namespace eul
{
namespace mpl
{
namespace mixin
{

template <template <typename> typename Predicate>
struct ability
{
};

template <template <typename> typename Ability, std::size_t Index,
          typename... Args>
struct ability_to_index_impl;


template <template <typename> typename Ability, std::size_t Index>
struct ability_to_index_impl<Ability, Index>
{
    constexpr static std::size_t value = -1;
};

template <template <typename> typename Ability, std::size_t Index, typename Arg,
          typename... Args>
struct ability_to_index_impl<Ability, Index, Arg, Args...>
{
    static_assert(Ability<Arg>::value, "type");
    constexpr static std::size_t value
        = Ability<Arg>::value == true
              ? Index
              : ability_to_index_impl<Ability, Index + 1, Args...>::value;
};

template <template <typename> typename Ability, typename... Args>
struct ability_to_index;

template <template <typename> typename Ability, typename... Args>
struct ability_to_index<Ability, std::tuple<Args...>>
{
    constexpr static std::size_t value
        = ability_to_index_impl<Ability, 0, Args...>::value;
};

template <typename MixedObject>
struct access
{
    constexpr access(void* data) : object_(*static_cast<MixedObject*>(data))
    {
    }

    template <typename DataType>
    DataType& get()
    {
        return std::get<data_t<DataType>>(object_.data_);
    }

    template <template <typename> typename Ability>
    auto& get_by_ability()
    {
        return std::get<
            ability_to_index<Ability, decltype(object_.data_)>::value>(
            object_.data_);
    }

    template <template <typename> typename T>
    auto& operator[](ability<T>)
    {
        return get_by_ability<T>();
    }

private:
    MixedObject& object_;
};


template <template <typename> typename... Types>
struct mixin
    : public inherit_from<
          typename filter<is_interface, Types<mixin<Types...>>...>::type>
{
public:
    using DataType = typename filter<is_data, Types<mixin<Types...>>...>::type;
    DataType data_;

    friend class access<mixin>;
};

} // namespace mixin
} // namespace mpl
} // namespace eul
