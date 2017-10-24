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

namespace nifty {
namespace infusion {


template<NLabelsType N_LABELS>
class SecondOrderFunction
:   public DiscreteValueFunctionBase<SecondOrderFunction<N_LABELS>>,
    public std::array<float, N_LABELS>
{
    typedef DiscreteValueFunctionBase<SecondOrderFunction<N_LABELS>> DiscreteValueFunctionBaseType;
    typedef std::array<float, N_LABELS> ArrayBaseType;
    
public:
    using DiscreteValueFunctionBaseType::operator();

    SecondOrderFunction()
    :   DiscreteValueFunctionBaseType(),
        ArrayBaseType()
    {
    }

    SecondOrderFunction(std::initializer_list<float> values)
    :   DiscreteValueFunctionBaseType(),
        ArrayBaseType()
    {
        NIFTY_CHECK_OP(this->size(),==, N_LABELS, "invalid size");
        std::copy(values.begin(), values.end(), this->begin());
    }

    constexpr auto n_labels(std::size_t i)const{
        return N_LABELS;
    }
    constexpr auto arity()const{
        return 2;
    }
    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return this->operator[](labels[0]);
    }

};





template<ArityType N_LABELS>
struct StaticPropertyArity<SecondOrderFunction<N_LABELS>>
: public StaticArity<2>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<SecondOrderFunction<N_LABELS>>
: public StaticShape<N_LABELS, N_LABELS>{
};


template<>
struct StaticPropertyShape<SecondOrderFunction<0>>
: public NoneType{
};



}
}