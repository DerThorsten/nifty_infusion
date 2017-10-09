#include "doctest.h"

#include "nifty/infusion/optimizers/inplace/qpbo.hpp"


#include "nifty/infusion/functions/value_functions/potts_function.hpp"
#include "nifty/infusion/functions/value_functions/unary_function.hpp"

TEST_CASE("infusion externals ") {




    auto size = 5;
    auto n_var = size*size;
    typedef nifty::infusion::Qpbo<float> SolverType;
    typedef typename SolverType::Parameters ParametersType;

    ParametersType parameters;
    nifty::infusion::Qpbo<float> qpbo(n_var, parameters);

    typedef nifty::infusion::UnaryFunction<2> UnaryType;
    typedef nifty::infusion::PottsFunction<2> PottsType;

    for(auto i=0; i<size; ++i)
    for(auto j=0; j<size; ++j){

        const auto vi0 = i*size+j;
        qpbo.add_factor({vi0}, UnaryType({0.0,1.0}));

        if(i+1<size){
            const auto vi1 = (i+1)*size+j;
            qpbo.add_factor({vi0, vi1}, PottsType(1.0));
        }   
        if(j+1<size){
            const auto vi1 = i*size+(j+1);
            qpbo.add_factor( {vi0, vi1}, PottsType(1.0));
        }
    }

    
}