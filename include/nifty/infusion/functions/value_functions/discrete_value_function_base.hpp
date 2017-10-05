#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
 

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/value_function_base.hpp"

namespace nifty {
namespace infusion {


template<class DERIVED>
class DiscreteValueFunctionBase : public ValueFunctionBase<DERIVED>{
public:
    typedef DERIVED DerivedType;
    auto n_labels(const std::size_t i)const{
        return this->derived_cast().n_labels(i);
    }
    auto bounds(const std::size_t i)const{
        const auto nl = this->derived_cast().n_labels(i);
        typedef typename std::remove_cv<decltype(nl)>::type NLabelsType;
        return std::make_pair(static_cast<NLabelsType>(0),nl-1);
    }

    auto operator()(const DiscreteLabelType l0)const{
        return this->derived_cast().operator()(&l0);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1)const{
        const DiscreteLabelType l[2] = {l0, l1};
        return this->derived_cast().operator()(l);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1, 
                    const DiscreteLabelType l2)const{
        const DiscreteLabelType l[3] = {l0, l1, l2};
        return this->derived_cast().operator()(l);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1, 
                    const DiscreteLabelType l2, const DiscreteLabelType l3)const{
        const DiscreteLabelType l[4] = {l0, l1, l2, l3};
        return this->derived_cast().operator()(l);
    }
  
};


}
}