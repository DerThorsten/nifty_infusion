#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
 


#include "nifty/infusion/functions/function_base.hpp"

namespace nifty {
namespace infusion {




template<class DERIVED>
class DiscreteConstraintBase : public ConstraintBase<DERIVED>{
public:

    auto n_labels(const std::size_t i)const{
        return this->derived_cast().n_labels(i);
    }
    auto bounds(const std::size_t i)const{
        const auto nl = this->derived_cast().n_labels(i);
        typedef typename std::remove_cv<decltype(nl)>::type NLabelsType;
        return std::make_pair(static_cast<NLabelsType>(0),nl-1);
    }

};


}
}