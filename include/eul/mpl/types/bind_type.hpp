#pragma once

namespace eul
{
namespace mpl
{
namespace types
{

template <typename Key, typename Value>
struct binded
{
    using KeyType = Key;
    using ValueType = Value;

    ValueType value;
};

template <typename Key>
struct bind_type
{
    template <typename ValueType>
    constexpr static auto to(ValueType&& value)
    {
        return binded<Key, ValueType>{std::move(value)};
    }
};

} // namespace types
} // namespace mpl
} // namespace eul
