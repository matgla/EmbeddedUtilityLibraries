#include <tuple>
#include <string>
#include <memory>
#include <type_traits>
#include <iostream>

template <typename... Ts>
struct interface
{
    static constexpr bool is_interface = true;
};

template <typename... Types>
struct add_interfaces
{};

template <typename Type, typename... Rest>
struct add_interface : public Type
{};

template <typename... Types>
struct combiner : public add_interfaces<Types...>
{
    using data_type = std::tuple<Types...>;

private:
    data_type data_;
};


struct InterfaceFoo
{
    void foo() {};
};

struct InterfaceBar
{
    void bar() {};
};

template <typename T>
concept bool Predicate = requires (T a)
{
    { T::value }
};

struct A
{
    std::string str;
};

template <typename Tuple, std::size_t Index>
constexpr void for_each_impl(const auto& fn, Tuple& tuple)
{
    fn(std::get<Index>(tuple));
    if constexpr (Index + 1 < std::tuple_size<Tuple>::value)
    {
        for_each_impl<Tuple, Index + 1>(fn, tuple);
    }
}

template <typename Tuple, std::size_t Size = 0>
constexpr void for_each(Tuple& t, const auto& fn)
{
    for_each_impl<Tuple, 0>(fn, t);
}

int main()
{
    using OnlyPrimitives = typename filter<std::is_integral, int, double, A, std::unique_ptr<int>, std::string, long double, long int>::type;

    OnlyPrimitives o;
    for_each(o, [](auto a) {
        std::cout << typeid(a).name() << std::endl;
    });

}
