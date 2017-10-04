#pragma once

#include <cstddef>     // std::size_t 
#include <initializer_list>

#include "boost/container/flat_set.hpp"

#include "nifty/infusion/infusion.hpp"
#include "nifty/infusion/factors/discrete_factor_base.hpp"



namespace nifty {
#pragma once
namespace infusion {






    template<class DISCRETE_FUNCTION>
    class FunctionViewDiscreteFactor;

    
    template<class DISCRETE_FUNCTION>
    class FunctionViewDiscreteFactor : 
    public DiscreteFactorBase<FunctionViewDiscreteFactor<DISCRETE_FUNCTION>>
    {
    private:
        typedef DISCRETE_FUNCTION DiscreteFunctionType;
        typedef FunctionViewDiscreteFactor<DiscreteFunctionType> SelfType;
        typedef typename FactorFunction<SelfType>::type    FunctionType;
        typedef typename FactorVariableSet<SelfType>::type VariableSetType;

    public:

        template<class VI_ITER>
        FunctionViewDiscreteFactor(const FunctionType & function, VI_ITER vi_begin, VI_ITER vi_end)
        :   function_(&function),
            variables_set_(vi_begin, vi_end){
        }

        template<class VI>
        FunctionViewDiscreteFactor(const FunctionType & function, std::initializer_list<VI> variables)
        :   FunctionViewDiscreteFactor(function, variables.begin(), variables.end()){
        }

        const auto & function()const{
            return *function_;
        }

        const auto & variables_set()const{
            return variables_set_;
        }


    private:


        const FunctionType * function_;
        VariableSetType variables_set_;
    };


    template< class DISCRETE_FUNCTION>
    struct FactorFunction<FunctionViewDiscreteFactor<DISCRETE_FUNCTION>>{
        typedef DISCRETE_FUNCTION type;
    };



    template< class DISCRETE_FUNCTION>
    struct FactorVariableSet<FunctionViewDiscreteFactor<DISCRETE_FUNCTION>>{
        typedef boost::container::flat_set<VariableIndexType> type;
    };




}
}