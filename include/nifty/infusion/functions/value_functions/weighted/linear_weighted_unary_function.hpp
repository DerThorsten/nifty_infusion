#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <vector>

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/weighted/linear_weighted_discrete_value_function_base.hpp"

namespace nifty {
namespace infusion {




template<class DERIVED>
class LinearWeightedUnaryFunctionBase : public LinearWeightedDiscreteValueFunctionBase<DERIVED>{
public:
    typedef DERIVED DerivedType;

    auto arity()const{
        return 1;
    }

    template<class LABELS,typename std::enable_if<!std::is_integral<LABELS>::value,int>::type = 0>
    auto operator()(const LABELS & labels)const{
        return this->derived_cast().operator()(labels[0]);
    }

    auto n_labels(auto i)const{
        return derived_cast()->size();
    }

};










template<class T = float, NLabelsType N_LABELS = 0>
class LinearWeightedPMapUnaryFunction
{
private:
    
public:

    enum WeightingScheme{
        ONE_WEIGHT_FOR_ALL,
        ONE_WEIGHT_PER_CLASS
    };  

    template<U>
    LinearWeightedPMapUnaryFunction(
        std::initializer_list<U> probs,
        const WeightingScheme weighting_scheme
    )
    :   BaseType(probs),
        weighting_scheme_(weighting_scheme)
    {
    }

    template<PROBS_ITER>
    LinearWeightedPMapUnaryFunction(
        PROBS_ITER probs_begin, 
        PROBS_ITER end, 
        const WeightingScheme weighting_type
    )
    :   BaseType(probs),
        weighting_scheme_(weighting_scheme)
    {
    }

    auto n_weights()const{
        if(weighting_type == ONE_WEIGHT_FOR_ALL){
            return 1;
        }
        else if(weighting_type == ONE_WEIGHT_PER_CLASS){
            values_->size();
        }
    }
    auto size()const{
        return values_->size();
    }
    auto operator()(const DiscreteLabel l0)const{
        return values_[l0];
    }


private:

    nifty::tools::TinyArray<T, std::size_t(N_LABELS), 16 > probs_;
    nifty::tools::TinyArray<T, std::size_t(N_LABELS), 16 > values_;
    WeightingScheme weighting_scheme_;

    boost::container::small_vector<std::size_t, 16> weight_indices_;
};





// template<>
// class LinearWeightedPMapUnaryFunction<0>
// :   public LinearWeightedPMapUnaryFunctionBase<LinearWeightedPMapUnaryFunction<0>>,
//     public std::vector<float>
// {
//     typedef LinearWeightedPMapUnaryFunctionBase<LinearWeightedPMapUnaryFunction<0>> LinearWeightedPMapUnaryFunctionBaseType;
//     typedef std::vector<float> VectorBaseType;
    

// public:
//     using LinearWeightedPMapUnaryFunctionBaseType::operator();
//     using VectorBaseType::VectorBaseType;


//     auto n_labels(std::size_t i)const{
//         return this->size();
//     }
//     auto operator()(const DiscreteLabelType & l0)const{
//         return (*this)[labels[0]];
//     }

// private:
// };







template<ArityType N_LABELS>
struct StaticPropertyArity<LinearWeightedPMapUnaryFunction<N_LABELS>>
: public StaticArity<1>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<LinearWeightedPMapUnaryFunction<N_LABELS>>
: public StaticShape<N_LABELS>{
};


template<>
struct StaticPropertyShape<LinearWeightedPMapUnaryFunction<0>>
: public NoneType{
};





}
}