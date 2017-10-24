#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <vector>

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/discrete_value_function_base.hpp"

namespace nifty {
namespace infusion {


template<class DERIVED>
class WeightedDiscreteValueFunctionBase : public DiscreteValueFunctionBase<DERIVED>{
public:
    typedef DERIVED DerivedType;

    // must have 
    auto n_weights()const{
        return this->derived_cast().n_weights();
    }
    auto weight_index(const std::size_t i)const{
        return this->derived_cast().weight_index(i);
    }
  
};


}
}