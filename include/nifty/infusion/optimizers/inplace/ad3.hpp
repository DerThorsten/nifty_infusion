#pragma once


#include <memory>
#include <algorithm>

#include "ad3/FactorGraph.h"
#include "nifty/tools/runtime_check.hpp"
#include "nifty/infusion/infusion.hpp"
#include "nifty/infusion/optimizers/inplace/inplace_discrete_graphical_model_optimizer_base.hpp"

namespace nifty {
namespace infusion {






    template<class VARIABLE_SPACE>
    class Ad3 : public InplaceDiscreteGraphicalModelOptimzerBase<Ad3<VARIABLE_SPACE>>
    {
    private:
    
    public:
        typedef VARIABLE_SPACE VariabeSpaceType;

        enum SolverType{
            AD3_LP,
            AD3_ILP,
            PSDD_LP
         };

        struct Parameters{
            SolverType  solver_type        {AD3_ILP};
            double      eta                {0.1};
            bool        adapt_eta          {false};
            uint64_t    steps              {1000};
            double      residual_threshold {1e-6};
            int         verbosity          {2};
        };

        Ad3(
            const VariabeSpaceType & variable_space,
            const Parameters & parameters
        )
        :   variable_space_(variable_space),
            n_variables_(variable_space.n_variables()),
            parameters_(parameters),
            factor_graph_(),
            multi_variables_(variable_space.n_variables()),
            multi_variables_local_(),
            posteriors_(),
            additional_posteriors_(),
            value_buffer_(),
            arg_(variable_space.n_variables()),
            inference_done_(false)
        {
            // fill space :
            //  - Create a multi-valued variable for variable of gm 
            //    and initialize unaries with 0
            for(auto vi=0; vi<n_variables_; ++vi){
                const auto n_labels = variable_space_.n_labels(vi);
                multi_variables_[vi] = factor_graph_.CreateMultiVariable(n_labels);
                for(auto l=0; l<n_labels; ++l){
                    multi_variables_[vi]->SetLogPotential(l,0.0);
                }
            }
        }


        template<class VARIABLES, class FUNCTION>
        void add_factor(
            const VARIABLES & variables,
            const FUNCTION & function
        ){
            const auto  arity = function.arity();

            if(arity == 1)
                this->add_unary_factor(variables, function);
            else
                this->add_higher_order_factor(variables, function, arity);

        }

        template<class VARIABLE, class FUNCTION>
        void add_factor(
            std::initializer_list<VARIABLE> variables,
            const FUNCTION & function    
        ){
            return this->add_factor(variables.begin(), function);
        }




        void optimize(){
            if(parameters_.solver_type == AD3_LP || parameters_.solver_type == AD3_ILP){
                factor_graph_.SetEtaAD3(parameters_.eta);
                factor_graph_.AdaptEtaAD3(parameters_.adapt_eta);
                factor_graph_.SetMaxIterationsAD3(parameters_.steps);
                factor_graph_.SetResidualThresholdAD3(parameters_.residual_threshold);
            }
            if(parameters_.solver_type == PSDD_LP){
                factor_graph_.SetEtaPSDD(parameters_.eta);
                factor_graph_.SetMaxIterationsPSDD(parameters_.steps);
            }

            // solve
            double value;

            if ( parameters_.solver_type == AD3_LP){
                std::cout<<"ad3  lp\n";
                factor_graph_.SolveLPMAPWithAD3(&posteriors_, &additional_posteriors_, &value);
            }
            if ( parameters_.solver_type == AD3_ILP){
                std::cout<<"ad3 ilp\n";
                factor_graph_.SolveExactMAPWithAD3(&posteriors_, &additional_posteriors_, &value);
            }
            if (parameters_.solver_type == PSDD_LP){
                std::cout<<"ad3 psdd lp\n";
                factor_graph_.SolveLPMAPWithPSDD(&posteriors_, &additional_posteriors_, &value);
            }

            // make arg
            uint64_t c = 0;
            for(auto vi=0; vi<n_variables_; ++vi){
                const auto nl = variable_space_.n_labels(vi);
                auto begin = posteriors_.begin() + c;
                const auto best_label = std::distance(begin, std::max_element(begin, begin + nl));
                arg_[vi] = best_label;
                c += nl;
            }
            inference_done_ = true;
        }

        auto state(const VariableIndexType vi)const{
           return arg_[vi];
        }

        
        
        const VariabeSpaceType & variable_space()const{
            return variable_space_;
        }

    private:

        template<class VARIABLES, class FUNCTION>
        void add_unary_factor(
            const VARIABLES & variables,
            const FUNCTION & function
        ){
            const auto nl = function.n_labels(0);
            const auto vi0 = variables[0];
            for(auto l=0; l<nl; ++l){
                const auto logP = multi_variables_[vi0]->GetLogPotential(l);
                const auto val  = function(l) * -1.0;
                multi_variables_[vi0]->SetLogPotential(l,logP+val);
            }
        }

        template<class VARIABLES, class FUNCTION>
        void add_higher_order_factor(
            const VARIABLES & variables,
            const FUNCTION & function,
            const ArityType arity
        ){
           
            value_buffer_.resize(function.size());
            function.c_order_buffer(value_buffer_,[](const auto & val){
                return -1.0 * val;
            });

            // local variables
            multi_variables_local_.resize(arity);
            std::vector<AD3::MultiVariable*> multi_variables_local(arity);
            for(auto v=0; v<arity; ++v)
                multi_variables_local_[v] = multi_variables_[variables[v]];


            // create higher order factor
            factor_graph_.CreateFactorDense(multi_variables_local_,value_buffer_);
        }







        const VariabeSpaceType & variable_space_;
        NVariablesType n_variables_;
        Parameters parameters_;
        

        AD3::FactorGraph factor_graph_;
        std::vector<AD3::MultiVariable*> multi_variables_;
        std::vector<AD3::MultiVariable*> multi_variables_local_;
        std::vector<double> posteriors_;
        std::vector<double> additional_posteriors_;
        std::vector<double> value_buffer_;
        std::vector<DiscreteLabelType> arg_;
        bool inference_done_;




        
    };


}   
}