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
        };

        Qpbo(
            const NVariablesType n_variables,
            const Parameters & parameters
        )
        :   n_variables_(n_variables),
            parameters_(parameters),
            internal_qpbo_(new InternalQpboType(n_variables,parameters.reserve_edges))
        {
            internal_qpbo_->AddNode(n_variables);
        }


        template<class FUNCTION,class VARIABLES>
        void add_factor(
            const FUNCTION & function,
            const VARIABLES & variables
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
            }
        }

    private:

        NVariablesType n_variables_;
        Parameters parameters_;

        std::unique_ptr<InternalQpboType> internal_qpbo_;
        
        
    };


}   
}