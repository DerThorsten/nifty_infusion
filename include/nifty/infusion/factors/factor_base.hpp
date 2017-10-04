#pragma once
#include <cstddef>     // std::size_t 



namespace nifty {
namespace infusion {



    template< class FACTOR>
    struct FactorFunction;

    template< class FACTOR>
    struct FactorVariableSet;

    template<class DERIVED>
    class FactorBase{

    public:

        typedef DERIVED DerivedType;
        typedef typename FactorFunction<DerivedType>::type    FunctionType;
        typedef typename FactorVariableSet<DerivedType>::type VariableSetType;

        // must have
        auto && function() const {
            return std::forward<FunctionType>(this->derived_cast().function());
        }

        auto && variable_set() const {
            return std::forward<VariableSetType>(this->derived_cast().variable_set());
        }

    };

}
}