#pragma once
#include <cstddef>     // std::size_t 


#include "nifty/infusion/factors/factor_base.hpp"


namespace nifty {
namespace infusion {




    template<class DERIVED>
    class DiscreteFactorBase : public FactorBase<DERIVED>
    {

    public:

        typedef DERIVED DerivedType;
        typedef typename FactorFunction<DerivedType>::type    FunctionType;
        typedef typename FactorVariableSet<DerivedType>::type VariableSetType;


    };

}
}