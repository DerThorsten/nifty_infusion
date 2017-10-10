#pragma once


#include <memory>


#include "qpbo/QPBO.h"
#include "nifty/tools/runtime_check.hpp"
#include "nifty/infusion/infusion.hpp"
#include "nifty/infusion/optimizers/inplace/inplace_optimizer_base.hpp"

namespace nifty {
namespace infusion {






    template<class T>
    class Qpbo : public InplaceOptimzerBase<Qpbo<T>>
    {
    private:
        typedef T QpboInternalValueType; 
        typedef qpbo::QPBO<QpboInternalValueType> InternalQpboType;
    public:

        struct Parameters{
            int reserve_edges{0}; 
            bool enforce_skip_merge_parallel_edges{false};

            bool probeing{false};
            int  n_improve{0};
            bool strong_persistency{false};

        };

        Qpbo(
            const NVariablesType n_variables,
            const Parameters & parameters
        )
        :   n_variables_(n_variables),
            parameters_(parameters),
            internal_qpbo_(new InternalQpboType(n_variables,parameters.reserve_edges)),
            might_need_parallel_edge_merging_(false)
        {
            internal_qpbo_->AddNode(n_variables);
        }


        template<class VARIABLES, class FUNCTION>
        void add_factor(
            const VARIABLES & variables,
            const FUNCTION & function
        ){
            // OPTIMIZE!!
            const auto arity = function.arity();
            NIFTY_CHECK_OP(arity,<=,2,"wrong arity for qpbo");
            if(arity == 1){
                NIFTY_CHECK_OP(function.n_labels(0),==,2,"wrong number of labels for qpbo");
                const auto v0 = variables[0];

                internal_qpbo_->AddUnaryTerm(v0,
                    function(0),function(1));
            }
            else if(arity == 2){
                NIFTY_CHECK_OP(function.n_labels(0),==,2,"wrong number of labels for qpbo");
                NIFTY_CHECK_OP(function.n_labels(1),==,2,"wrong number of labels for qpbo");
                const auto v0 = variables[0];
                const auto v1 = variables[1];
                internal_qpbo_->AddPairwiseTerm(v0,v1,
                    function(0,0),function(0,1),
                    function(1,0),function(1,1));
                might_need_parallel_edge_merging_ = true;
            }
            
            needs_optimization_ = true;
        }

        template<class VARIABLE, class FUNCTION>
        void add_factor(
            std::initializer_list<VARIABLE> variables,
            const FUNCTION & function    
        ){
            return this->add_factor(variables.begin(), function);
        }



        template<class RESULT>
        void optimize(RESULT & result){

            if(might_need_parallel_edge_merging_ && ! parameters_.enforce_skip_merge_parallel_edges){
                internal_qpbo_->MergeParallelEdges();
            }

            if(needs_optimization_){
                internal_qpbo_->Solve();
            }

            for(auto vi=0; vi<n_variables_; ++vi){
                auto l = internal_qpbo_->GetLabel(vi);
                if(l==0 || l==1){
                    result[vi] = l;
                }
                else{
                    result[vi] = 0;
                }
            }
        }

        auto optimize(){
            std::vector<DiscreteLabelType>  result(n_variables_);
            this->optimize(result);
            return result;
        }




    private:


        NVariablesType n_variables_;
        Parameters parameters_;
        std::unique_ptr<InternalQpboType> internal_qpbo_;

        // state machinery
        bool might_need_parallel_edge_merging_;
        bool needs_optimization_;
        
    };


}   
}