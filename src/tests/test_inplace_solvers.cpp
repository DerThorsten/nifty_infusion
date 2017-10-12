#include "doctest.h"

#include <random>


#include "nifty/infusion/optimizers/inplace/ad3.hpp"
#include "nifty/infusion/optimizers/inplace/qpbo.hpp"


#include "nifty/infusion/variable_space/simple_discrete_variable_space.hpp"
#include "nifty/infusion/functions/value_functions/potts_function.hpp"
#include "nifty/infusion/functions/value_functions/unary_function.hpp"





TEST_CASE("test_inplace_solver_qpbo") {

    using namespace nifty::infusion;

    const static  NVariablesType n_variables = 10;

    // 10 variables with 2 labels
    typedef SimpleDiscreteVariableSpace<2,n_variables> VariabeSpaceType;
    typedef UnaryFunction<2> UnaryFunctionType;
    typedef PottsFunction<2> PottsFunctionType;

    typedef Qpbo<VariabeSpaceType> QpboType;
    typedef typename QpboType::Parameters QpboParamType;


    typedef Ad3<VariabeSpaceType> Ad3Type;
    typedef typename Ad3Type::Parameters Ad3ParamType;


    VariabeSpaceType variable_space;


    // Solvers:


    Ad3ParamType ad3_param;
    Ad3Type ad3_opt(variable_space, ad3_param);

    QpboParamType qpbo_param;
    QpboType qpbo_opt(variable_space, qpbo_param);



    // rand init
    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<float> unary_dist(0, 1);
    std::uniform_real_distribution<float> beta_dist(0.0, 0.5);



    // add unaries
    for(auto vi=0; vi<n_variables; ++vi){
        UnaryFunctionType unary_function({
            unary_dist(e1),
            unary_dist(e1)
        });
        ad3_opt.add_factor({vi}, unary_function);
        qpbo_opt.add_factor({vi}, unary_function);
    }

    // add second order
    for(auto vi=0; vi<n_variables-1; ++vi){
        PottsFunctionType potts_function(1);//beta_dist(e1));
        ad3_opt.add_factor({vi, vi+1}, potts_function);
        qpbo_opt.add_factor({vi, vi+1}, potts_function);
    }


    // optimize
    ad3_opt.optimize();
    qpbo_opt.optimize();



    for(auto vi=0; vi<n_variables; ++vi){
        const auto ad3_state = ad3_opt.state(vi);
        const auto qpbo_state = qpbo_opt.state(vi);
        CHECK_EQ(ad3_state, qpbo_state);
    }



    
}