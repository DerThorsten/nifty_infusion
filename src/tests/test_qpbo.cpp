#include "doctest.h"


#include "test_inplace_solver.hpp"


#include "nifty/infusion/optimizers/inplace/qpbo.hpp"
#include "nifty/infusion/functions/value_functions/potts_function.hpp"
#include "nifty/infusion/functions/value_functions/unary_function.hpp"











TEST_CASE("test_inplace_solver_qpbo") {





    auto size = 5;
    auto n_var = size*size;
    typedef nifty::infusion::Qpbo<float> SolverType;
    typedef typename SolverType::Parameters ParametersType;



    {
        auto n_iter = 10;

        for(auto i=0; i<10; ++i){

            ParametersType param_qpbo;
            auto beta = 0.5;
            auto n_labels = 2;
            auto negative_regularizer = true;
            auto seed = 42;

            {
                auto solver_qpbo = nifty::infusion::make_potts_grid_optimizer<SolverType>(
                    param_qpbo,{3,3},n_labels,beta,
                    negative_regularizer, seed
                );
                auto res = solver_qpbo->optimize();
            }
        }

    }






    
    // nifty::infusion::Qpbo<float> qpbo(n_var, parameters);

    // typedef nifty::infusion::UnaryFunction<2> UnaryType;
    // typedef nifty::infusion::PottsFunction<2> PottsType;

    // for(auto i=0; i<size; ++i)
    // for(auto j=0; j<size; ++j){

    //     const auto vi0 = i*size+j;
    //     qpbo.add_factor({vi0}, UnaryType({0.0,1.0}));

    //     if(i+1<size){
    //         const auto vi1 = (i+1)*size+j;
    //         qpbo.add_factor({vi0, vi1}, PottsType(1.0));
    //     }   
    //     if(j+1<size){
    //         const auto vi1 = i*size+(j+1);
    //         qpbo.add_factor( {vi0, vi1}, PottsType(1.0));
    //     }
    // }

    
}