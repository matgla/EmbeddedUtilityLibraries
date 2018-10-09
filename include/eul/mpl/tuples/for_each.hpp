#include <tuple>
#include <type_traits>

namespace eul
{
namespace mpl
{
namespace tuples
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

template <template <typename> typename Pred, typename Tuple, std::size_t Index>
constexpr void for_each_impl(const auto& fn, Tuple& tuple)
{
    if constexpr (Pred<typename std::tuple_element<Index, Tuple>::type>::value)
    {
        fn(std::get<Index>(tuple));
    }

    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Pred, Tuple, Index + 1>(fn, tuple);
    }
}

} // namespace detail

template <typename Tuple, std::size_t Size = 0>
constexpr void for_each(Tuple& t, const auto& fn)
{
    detail::for_each_impl<Tuple, 0>(fn, t);
}

template <template <typename> typename Pred, typename Tuple>
constexpr void for_each(Tuple& t, const auto& fn)
{
    detail::for_each_impl<Pred, Tuple, 0>(fn, t);
}

} // namespace tuples
} // namespace mpl
} // namespace eul
