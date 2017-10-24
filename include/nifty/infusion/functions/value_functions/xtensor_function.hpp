#pragma once 
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <vector>
#include <array>
#include <utility>
 

#include "nifty/tools/runtime_check.hpp"

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/discrete_value_function_base.hpp"



#include <xtensor/xexpression.hpp>
#include <xtensor/xtensor.hpp>



namespace nifty {
namespace infusion {


template<std::size_t ARITY>
class XTensorFunction
:   public DiscreteValueFunctionBase<XTensorFunction<ARITY>>,
    public xt::xtensor<float, ARITY>
{
    typedef DiscreteValueFunctionBase<XTensorFunction<ARITY>> DiscreteValueFunctionBaseType;
    typedef xt::xtensor<float, ARITY> TensorBase;
public:
    using TensorBase::TensorBase;
    using TensorBase::operator();
    using DiscreteValueFunctionBaseType::shape;


    auto arity()const{
        return ARITY;
    }

    auto n_labels(std::size_t i)const{
        return TensorBase::shape()[i];
    }

    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return this->element(labels.begin(), labels.end());
    }


};




template<std::size_t ARITY>
struct StaticPropertyArity<XTensorFunction<ARITY>>
: public StaticArity<ARITY>{
};

// template<std::size_t N_LABELS>
// struct StaticPropertyShape<UnaryFunction<N_LABELS>>
// : public StaticShape<N_LABELS>{
// };




}
}