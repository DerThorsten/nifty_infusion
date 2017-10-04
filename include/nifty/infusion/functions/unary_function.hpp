#pragma once 
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <vector>
#include <array>
#include <utility>
 

#include "nifty/tools/runtime_check.hpp"

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/discrete_function_base.hpp"

namespace nifty {
namespace infusion {


template<NLabelsType N_LABELS = 0>
class UnaryFunction;

template<>
class UnaryFunction<0>
:   public DiscreteFunctionBase<UnaryFunction<0>>
{
    typedef DiscreteFunctionBase<UnaryFunction<0>> BaseType;
    
public:
    using BaseType::operator();
    UnaryFunction(const NLabelsType n_labels=2)
    :   values_(n_labels, 0.0f){
    }

    auto n_labels(std::size_t i)const{
        return values_.size();
    }
    auto arity()const{
        return 1;
    }
    template<class LABELS>
    auto operator()(const LABELS & labels)const{
        return values_[labels[0]];
    }
private:
    std::vector<float> values_;
    
};


template<NLabelsType N_LABELS>
class UnaryFunction
:   public DiscreteFunctionBase<UnaryFunction<N_LABELS>>
{
    typedef DiscreteFunctionBase<UnaryFunction<N_LABELS>> BaseType;
    
public:
    using BaseType::operator();

    UnaryFunction()
    :   values_(){
    }

    UnaryFunction(std::initializer_list<float> values)
    :   values_(){
        NIFTY_CHECK_OP(values.size(),==, N_LABELS, "invalid size");
        std::copy(values.begin(), values.end(), values_.begin());
    }

    constexpr auto n_labels(std::size_t i)const{
        return N_LABELS;
    }
    constexpr auto arity()const{
        return 1;
    }
    template<class LABELS>
    auto operator()(const LABELS & labels)const{
        return values_[labels[0]];
    }
private:
    std::array<float, N_LABELS> values_;
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