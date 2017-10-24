#pragma once


#include <memory>
#include <algorithm>
#include <string>
#include <sstream>

#include <dai/daialg.h>
#include <dai/alldai.h>


#include "nifty/tools/runtime_check.hpp"
#include "nifty/infusion/infusion.hpp"
#include "nifty/infusion/optimizers/inplace/inplace_discrete_graphical_model_optimizer_base.hpp"

namespace nifty {
namespace infusion {




    struct JunctionTreeParameters{

        enum UpdateRule{
            HUGIN,
            SHSH
        };
        enum Heuristic{
            MIN_FILL,
            WEIGHTED_MIN_FILL,
            MIN_WEIGHT,
            MIN_NEIGHBORS
        };

        std::string to_dai_param_string()const{
            std::stringstream ss;
            std::string ur,hr;
            
            if(update_rule==HUGIN)
                ur = "HUGIN";
            else if(update_rule==SHSH)
                ur = "SHSH";
            
            if(heuristic==MIN_FILL)
                hr="MINFILL";
            else if(heuristic==WEIGHTED_MIN_FILL)
                hr = "WEIGHTEDMINFILL";
            else if(heuristic==MIN_WEIGHT)
                    hr = "MINWEIGHT";
            else if(heuristic==MIN_NEIGHBORS)
                hr = "MIN_NEIGHBORS";
            
            ss <<"JTREE["
               <<"updates="<<ur<<","
               <<"heuristic="<<hr<<","
               <<"inference="<<"MAXPROD"<<","
               <<"verbose="<<verbose<<"]";
            return ss.str();
        }

        UpdateRule update_rule{HUGIN};
        Heuristic heuristic{MIN_WEIGHT};
        size_t verbose{0};


    };





    template<class VARIABLE_SPACE, class SPECIAL_PARAMETERS>
    class Libdai : public InplaceDiscreteGraphicalModelOptimzerBase<Libdai<VARIABLE_SPACE, SPECIAL_PARAMETERS>>
    {
    private:
    
    public:
        typedef VARIABLE_SPACE VariabeSpaceType;

      
        struct Parameters
        : SPECIAL_PARAMETERS
        {

        };

        Libdai(
            const VariabeSpaceType & variable_space,
            const Parameters & parameters
        )
        :   variable_space_(variable_space),
            n_variables_(variable_space.n_variables()),
            parameters_(parameters),
            bound_(),
            dai_arg_(variable_space.n_variables()),
            dai_factor_graph_(nullptr),
            ia_(nullptr),
            dai_factors_(),
            dai_vars_(variable_space.n_variables()),
            string_alg_param_(parameters.to_dai_param_string()),
            value_buffer_(),
            dai_var_buffer_()
            {


            // fill space :
            //  - Create a multi-valued variable for variable of gm 
            //    and initialize unaries with 0
            for(auto vi=0; vi<n_variables_; ++vi){
                const auto n_labels = variable_space_.n_labels(vi);
                dai_vars_[vi] = ::dai::Var(vi, n_labels);

            }
        }

        ~Libdai(){
            if(ia_!= nullptr){
                delete ia_;
            }
            if(dai_factor_graph_ != nullptr){
                delete dai_factor_graph_;     
            }
        }

        template<class VARIABLES, class FUNCTION>
        void add_factor(
            const VARIABLES & variables,
            const FUNCTION & function
        ){
            const auto arity = function.arity();
            const auto size = function.size();

            if(dai_var_buffer_.size() < arity){
                dai_var_buffer_.resize(arity);
            }
            // create dai variables set
            for(auto a=0; a<arity; ++a){
                dai_var_buffer_[a] = dai_vars_[variables[a]];
            }
            dai::VarSet dai_varset(dai_var_buffer_.data(), dai_var_buffer_.data() + arity);

            // write function values in  continuous buffer and apply functor 
            // (from min sum semi-ring min-sum semi-ring)
            function.f_order_buffer(value_buffer_,[](const auto & val){
                return std::exp(-1.0 * val);
            });

            // add factor
            dai_factors_.emplace_back(dai_varset, value_buffer_.data());

        }

        template<class VARIABLE, class FUNCTION>
        void add_factor(
            std::initializer_list<VARIABLE> variables,
            const FUNCTION & function    
        ){
            return this->add_factor(variables.begin(), function);
        }




        void optimize(){
            if(dai_factor_graph_ != nullptr){
                throw std::runtime_error("cannot call optimize twice");
            }

            dai::FactorGraph * dai_factor_graph_ = new ::dai::FactorGraph(
                dai_factors_.begin(), dai_factors_.end(), 
                dai_vars_.begin(), dai_vars_.end());

            // TODO NOT CALL THIS TWICE
            ia_=dai::newInfAlgFromString(string_alg_param_,*dai_factor_graph_);
            ia_->init();


            try{
                ia_->run();
            }
            catch(const dai::Exception  & e) {
                std::stringstream ss;
                ss<<"libdai Error: "<<e.message(e.code());
                throw std::runtime_error(ss.str());
            }

            // make arg
            try{
               dai_arg_ = dai::findMaximum(*ia_);
            }
            catch(const dai::Exception  & e) {
                std::stringstream ss;
                ss<<"libdai Error: "<<e.message(e.code())<<" ";
                throw std::runtime_error(ss.str());
            }

        }

        auto state(const VariableIndexType vi)const{
           return dai_arg_[vi];
        }

        const VariabeSpaceType & variable_space()const{
            return variable_space_;
        }

    private:





        const VariabeSpaceType & variable_space_;
        NVariablesType n_variables_;
        Parameters parameters_;
        
        double bound_;
        std::vector<std::size_t> dai_arg_;

        ::dai::FactorGraph * dai_factor_graph_;
        ::dai::InfAlg * ia_;

        std::vector< ::dai::Factor > dai_factors_;
        std::vector< ::dai::Var > dai_vars_;

        std::string string_alg_param_;



        // buffers
        std::vector<double> value_buffer_;
        std::vector<::dai::Var> dai_var_buffer_;


        
    };

    template<class VARIABLE_SPACE>
    using LibdaiJunctionTree = Libdai<VARIABLE_SPACE, JunctionTreeParameters>;


}   
}