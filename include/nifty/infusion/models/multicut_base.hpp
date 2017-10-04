#pragma once

#include "nifty/infusion/models/discrete_model_base.hpp"

namespace nifty {
namespace infusion {




template<class DERIVED>
class MulticutBase;


template<class DERIVED>
class ConnectivityInducingGraph;


template<class DERIVED>
class MulticutBase : public DiscreteModelBase<DERIVED>{
    typedef DERIVED DerivedType;
public:
    typedef typename ConnectivityInducingGraph<DerivedType> ConnectivityInducingGraphType;
    
    const auto & connectivity_inducing_graph()const{
        this->derived_cast().connectivity_inducing_graph();
    }
};


} // end namespace nifty::infusion
} // end namespace nifty
