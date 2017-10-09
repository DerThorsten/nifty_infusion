#pragma once 
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
 

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/discrete_value_function_base.hpp"

namespace nifty {
namespace infusion {


template<NLabelsType N_LABELS = 0>
class PottsFunction;

template<>
class PottsFunction<0>
:   public DiscreteValueFunctionBase<PottsFunction<0>>
{
    typedef DiscreteValueFunctionBase<PottsFunction<0>> BaseType;
    
public:
    using BaseType::operator();
    PottsFunction(const NLabelsType n_labels=2, const float beta = 1.0f)
    :   n_labels_(n_labels),
        beta_(beta){
    }

    auto n_labels(std::size_t i)const{
        return n_labels_;
    }
    auto arity()const{
        return 2;
    }
    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return labels[0] != labels[1] ? beta_ : 0.0f;
    }
private:
    NLabelsType n_labels_;
    float beta_;
    
};


template<NLabelsType N_LABELS>
class PottsFunction
:   public DiscreteValueFunctionBase<PottsFunction<N_LABELS>>
{
    typedef DiscreteValueFunctionBase<PottsFunction<N_LABELS>> BaseType;
    
public:
    using BaseType::operator();
    PottsFunction(const float beta = 1.0f)
    :   beta_(beta){
    }

    constexpr auto n_labels(std::size_t i)const{
        return N_LABELS;
    }
    constexpr auto arity()const{
        return 2;
    }
    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return labels[0] != labels[1] ? beta_ : 0.0f;
    }
private:
    float beta_;
};





template<ArityType N_LABELS>
struct StaticPropertyArity<PottsFunction<N_LABELS>>
: public StaticArity<2>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<PottsFunction<N_LABELS>>
: public StaticShape<N_LABELS, N_LABELS>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyIsPotts<PottsFunction<N_LABELS>>
: public std::true_type{
};


template<>
struct StaticPropertyShape<PottsFunction<0>>
: public NoneType{
};







}
}