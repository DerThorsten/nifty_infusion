#include "doctest.h"

#include "nifty/infusion/functions/potts_function.hpp"
#include "nifty/infusion/factors/function_view_discrete_factor.hpp"


TEST_CASE("FunctionViewDiscreteFactor") {


    using namespace  nifty::infusion;

    SUBCASE("PottsFunction"){

        typedef PottsFunction<2> DiscreteFunctionType;
        typedef FunctionViewDiscreteFactor<DiscreteFunctionType> DiscreteFactorType;

        auto function = DiscreteFunctionType(1.0);
        auto factor   = DiscreteFactorType(function, {0,1});
         
    }

    
}