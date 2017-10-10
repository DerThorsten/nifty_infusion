#pragma once
#include "doctest.h"

#include <random>
#include <memory>

#include "nifty/infusion/functions/value_functions/potts_function.hpp"
#include "nifty/infusion/functions/value_functions/unary_function.hpp"

#include "nifty/infusion/infusion.hpp"



namespace nifty {
namespace infusion {


    template<class SOLVER>
    auto make_potts_grid_optimizer(
        const typename SOLVER::Parameters & parameters,
        std::initializer_list<int> shape_initalizer,
        NDisceteLabelsType  n_labels,
        double beta,
        bool negative_regularizer, 
        int seed
    ){
        std::vector<int> shape(shape_initalizer);

        
        std::mt19937 gen(seed);
        std::uniform_real_distribution<> dunary(0, 1);
        std::uniform_real_distribution<> dbeta(negative_regularizer ? -1.0*beta: 0.0, beta);


        auto n_variables = shape[0]*shape[1];
        
        std::unique_ptr<SOLVER> solver(new SOLVER(n_variables, parameters));

        typedef nifty::infusion::UnaryFunction<> UnaryType;
        typedef nifty::infusion::PottsFunction<> PottsType;


        for(auto x0=0; x0<shape[0]; ++x0)
        for(auto x1=0; x1<shape[1]; ++x1){

            const auto vi0 = x0*shape[1] + x1;

            auto unary = UnaryType(n_labels);
            for(auto & v : unary){
                v = dunary(gen);
            }
            solver->add_factor({vi0}, unary);

            if(x0+1<shape[0]){
                const auto vi1 = (x0+1)*shape[1] + x1;
                const auto reg = dbeta(gen);
                solver->add_factor({vi0, vi1}, PottsType(n_labels, reg));
            }   
            if(x1+1<shape[1]){
                const auto vi1 = (x0)*shape[1] + (x1+1);
                const auto reg = dbeta(gen);
                solver->add_factor( {vi0, vi1}, PottsType(n_labels, reg));
            }
        }


        return std::move(solver);
    }

}
}