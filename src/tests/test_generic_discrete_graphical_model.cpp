#include "doctest.h"

#include <vector>

#include "nifty/infusion/functions/potts_function.hpp"
#include "nifty/infusion/functions/unary_function.hpp"

#include "nifty/infusion/models/generic_discrete_graphical_model.hpp"
#include "nifty/infusion/variable_space/simple_discrete_variable_space.hpp"

TEST_CASE("GenericDiscreteGraphicalModel") {


    using namespace  nifty::infusion;


    SUBCASE("PottsFunction"){

        typedef PottsFunction<2> PottsFunctionType;
        typedef UnaryFunction<2> UnaryFunctionType;

        typedef SimpleDiscreteVariableSpace<2> VariableSpaceType;


        typedef GenericDiscreteGraphicalModel<
            VariableSpaceType,
            std::tuple<PottsFunctionType,UnaryFunctionType>
        > DiscreteGraphicalModelType;

        


        // 2x2 grid
        // 0 1
        // 2 3

        auto n_variables = 4;
        auto gm = DiscreteGraphicalModelType(n_variables);
        CHECK_EQ(gm.max_arity(),0);


        // add potts funtions once
        auto fid_potts = gm.add_function(PottsFunctionType(1.0));
        CHECK_EQ(gm.max_arity(),0);


        // unaries
        gm.add_factor(UnaryFunctionType({1.0f,0.0f}), {0});
        gm.add_factor(UnaryFunctionType({2.0f,0.0f}), {1});
        gm.add_factor(UnaryFunctionType({0.0f,0.0f}), {2});
        gm.add_factor(UnaryFunctionType({0.0f,1.0f}), {3});
        CHECK_EQ(gm.max_arity(),1);

        // add second order
        gm.add_factor(fid_potts, {0,1});
        gm.add_factor(fid_potts, {2,3});
        gm.add_factor(fid_potts, {0,2});
        gm.add_factor(fid_potts, {1,3});
        CHECK_EQ(gm.max_arity(),2);


        // evaluates
        std::vector<int> labels = {0,0,0,0};

        auto val = gm.eval_factors(labels);
       
         
    }

    
}