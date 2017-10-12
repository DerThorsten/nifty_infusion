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


template<NLabelsType N_LABELS = 0>
class UnaryFunction;

template<>
class UnaryFunction<0>
:   public  DiscreteValueFunctionBase<UnaryFunction<0>>,
    public std::vector<float>
{
    typedef DiscreteValueFunctionBase<UnaryFunction<0>> DiscreteValueFunctionBaseType;
    typedef std::vector<float> VectorBaseType;
    
public:
    using DiscreteValueFunctionBaseType::operator();
    using VectorBaseType::VectorBaseType;

    //UnaryFunction(const NLabelsType n_labels=2)
    //:   values_(n_labels, 0.0f){
    //}

    auto n_labels(std::size_t i)const{
        return this->size();
    }
    auto arity()const{
        return 1;
    }

    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return this->operator[](labels[0]);
    }

private:
    //std::vector<float> values_;
    
};


template<NLabelsType N_LABELS>
class UnaryFunction
:   public DiscreteValueFunctionBase<UnaryFunction<N_LABELS>>,
    public std::array<float, N_LABELS>
{
    typedef DiscreteValueFunctionBase<UnaryFunction<N_LABELS>> DiscreteValueFunctionBaseType;
    typedef std::array<float, N_LABELS> ArrayBaseType;
    
public:
    using DiscreteValueFunctionBaseType::operator();

    UnaryFunction()
    :   DiscreteValueFunctionBaseType(),
        ArrayBaseType()
    {
    }

    UnaryFunction(std::initializer_list<float> values)
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
        return 1;
    }
    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return this->operator[](labels[0]);
    }

};





template<ArityType N_LABELS>
struct StaticPropertyArity<UnaryFunction<N_LABELS>>
: public StaticArity<1>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<UnaryFunction<N_LABELS>>
: public StaticShape<N_LABELS>{
};


template<>
struct StaticPropertyShape<UnaryFunction<0>>
: public NoneType{
};



}
}