#pragma once

#include "nifty/infusion/models/discrete_model_base.hpp"

namespace nifty {
namespace infusion {



template<class DERIVED>
class DiscreteGraphicalModelBase : public DiscreteModelBase<DERIVED>{
public:

    template<class LABELS>
    auto eval_factors(const LABELS & labels)const{

        const auto & d = this->derived_cast();

        // this can be optimized
        const auto size =d.max_arity();
        std::vector<DiscreteLabelType> flabels(size);
        auto val = 0.0;
        d.for_each_factor([&](auto && index, auto && factor){
            auto && var_set = factor.variables_set();
            auto i = 0;
            for(auto var : var_set){
                flabels[i] = var;
                ++i;
                val += factor.function()(flabels);
            }
        });

        return val;

    }
};


} // end namespace nifty::infusion
} // end namespace nifty
