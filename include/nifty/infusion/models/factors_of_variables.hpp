#pragma once

#include <vector>

#include <boost/container/flat_set.hpp>

#include "nifty/meta/tuple.hpp"
#include "nifty/infusion/models/factor_index.hpp"

namespace nifty {
namespace infusion {


    ///\cond
    namespace detail_infusion{
        template<uint64_t TUPLE_INDEX>
        using FactorIndexSet = boost::container::flat_set<FactorIndex<TUPLE_INDEX>>;

        template<class GM>
        class FactorsOfVariable : public meta::GenerateTuple<
            std::tuple_size<typename GM::FactorTuple>::value,
            FactorIndexSet
        >::type{
        public:
            template<uint64_t TUPLE_INDEX>
            void insert(const FactorIndex<TUPLE_INDEX> & index){
                std::get<TUPLE_INDEX>(*this).insert(index);
            }
        };
    }
    ///\endcond

 
    template<class GM>
    class FactorsOfVariables{
        
    public:
        
        typedef GM GraphicalModelType;
        

        FactorsOfVariables(const GraphicalModelType & graphical_model)
        :   graphical_model_(graphical_model),
            factors_of_variables_(graphical_model.n_variables())
        {
            graphical_model_.for_each_factor([&](auto && index, auto && factor){
                auto && variables_set = factor.variables_set();
                for(const auto variable : variables_set){
                    factors_of_variables_[variable].insert(index);
                }
            });
        }

        template<class F>
        void for_each_factor(const VariableIndexType variable, F && f){
            
            const auto tuple = factors_of_variables_[variable];
            nifty::tools::for_each(tuple,[&](auto && factor_index_set){
                for(const auto & factor_index : factor_index_set){
                    auto && factor = graphical_model_[factor_index];
                    f(factor_index, std::forward<std::decay_t<decltype(factor)>>(factor));
                }
            });            
        }

    private:    
        typedef detail_infusion::FactorsOfVariable<GraphicalModelType> FactorsOfVariableType;

        const GraphicalModelType & graphical_model_;

        std::vector<FactorsOfVariableType> factors_of_variables_;

    };


}
}