#pragma once

#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
 

#include "nifty/infusion/infusion.hpp"

namespace nifty {
namespace infusion {






template<ArityType ARITY>
struct StaticArity : public std::integral_constant<ArityType, ARITY>{
};

template<NLabelsType ... VALS>
struct StaticShape : public std::integer_sequence<NLabelsType, VALS ...>{
};



// static properties to overload

template<class FUNCTION>
struct StaticPropertyArity : public NoneType {}; 

template<class FUNCTION>
struct StaticPropertyShape : public NoneType {}; 

template<class FUNCTION>
struct StaticPropertyIsPotts : public NoneType {}; 



}
}