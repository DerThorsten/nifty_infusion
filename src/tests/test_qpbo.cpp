#include "doctest.h"

#include "nifty/infusion/optimizers/inplace/qpbo.hpp"

TEST_CASE("infusion externals ") {


    auto size = 5;
    auto n_var = size*size;
    typedef nifty::infusion::Qpbo<float> SolverType;
    typedef typename SolverType::Parameters ParametersType;

    ParametersType parameters;
    nifty::infusion::Qpbo<float> qpbo(n_var, parameters);


    
}