#pragma once 

#include <tuple>
#include <type_traits>
#include <string>

namespace eul
{
    template<typename Tuple, typename Type> 
    struct has_type;
    
    template<typename Type, typename... Args>
    struct has_type<std::tuple<Args...>, Type> : std::disjunction<std::is_same<Type, Args>...>
    {
    };
} // namespace eul