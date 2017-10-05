#pragma once

#include <tuple>
#include <type_traits>

namespace nifty{
namespace meta{

    template <class T, class Tuple>
    struct FindTypeInTuple;

    template<std::size_t VAL>
    using SizeT = std::integral_constant<std::size_t, VAL>;


    template <class T, class... Types>
    struct FindTypeInTuple<T, std::tuple<T, Types...>> 
    :   SizeT<0>{ 
    };

    


}
}