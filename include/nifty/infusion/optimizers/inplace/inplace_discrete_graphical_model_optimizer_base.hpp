#pragma once


#include <xtensor/xexpression.hpp>
#include <xtensor/xview.hpp>


#include "nifty/infusion/functions/value_functions/unary_function.hpp"


namespace nifty {
namespace infusion {
    

    template<class DERIVED>
    class InplaceDiscreteGraphicalModelOptimzerBase{
    public:
        typedef DERIVED DerivedType;


        // must have
        const auto & variable_space() const {
            return this->derived_cast().variable_space();
        }

        auto state(const VariableIndexType vi) const {
            return this->derived_cast().state(vi);
        }

        




        auto n_variables() const {
            return this->variable_space().n_variables();
        }


        // adding batch factors
        template<class EXPRESSION>
        void add_unaries(
            const xt::xexpression<EXPRESSION> & unaries_expression
        ){
            typedef UnaryFunction<> UnaryFunctionType;
            const auto unaries = unaries_expression.derived_cast();
            const auto & shape = unaries.shape();
            const auto n_labels = shape[1];
            for(auto vi=0; vi< this->n_variables(); ++vi){
                const auto unary_array_for_vi = xt::view(unaries, vi,xt::all());
                UnaryFunctionType unary_function(n_labels);
                std::copy(unary_array_for_vi.begin(), unary_array_for_vi.end(), 
                    unary_function.begin());
                
                // add the unary factor
                this->derived_cast().add_factor({vi}, unary_function);
            } 

        }







        


        // optimality
        bool is_optimal()const{
            return false;
        }


        // partial optimality
        bool is_partial_optimal(const VariableIndexType vi) const {

            return this->derived_cast().is_optimal() ? 
                true : false;
        }

        // bool could_be_optimal(const VariableIndexType vi, const DiscreteLabelType state)const{
        //     if(this->derived_cast().is_optimal())
        //         return this->derived_cast().state(vi) == state ? true : false;
        //     else
        //         return true;
        // }

        





        





        DerivedType & derived_cast(){
            return static_cast<DerivedType &>(*this);
        }
        const DerivedType & derived_cast() const {
            return static_cast<const DerivedType &>(*this);
        }   





    };

}
}