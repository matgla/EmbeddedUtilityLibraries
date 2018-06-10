#include <tuple>
#include <type_traits>

namespace eul
{
namespace generics
{
namespace detail
{

template <typename Tuple, std::size_t Index>
constexpr void for_each_impl(const auto& fn, Tuple& tuple)
{
    fn(std::get<Index>(tuple));
    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Tuple, Index + 1>(fn, tuple);
    }
}

} // namespace detail

template <typename Tuple, std::size_t Size = 0>
constexpr void for_each(Tuple& t, const auto& fn)
{
    detail::for_each_impl<Tuple, 0>(fn, t);
}

} // namespace generics
} // namespace eul
