#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <vector>

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/weighted/weighted_discrete_value_function_base.hpp"

namespace nifty {
namespace infusion {


template<class DERIVED>
class LinearWeightedDiscreteValueFunctionBase : public WeightedDiscreteValueFunctionBase<DERIVED>{
public:
    typedef DERIVED DerivedType;
    

    template<class STATES, class GRAD, class ACC>
    void accumulate_gradient(const STATES & states,GRAD & grad,ACC && accumulator)const{
        this->derived_cast().accumulate_gradient(states, grad, accumulator);
    }

};


}
}