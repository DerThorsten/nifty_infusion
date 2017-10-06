#include "nifty/infusion/variable_space/discrete_variable_space_base.hpp"


namespace nifty {
namespace infusion {




template<NLabelsType NUMBER_OF_LABELS>
class SimpleDiscreteVariableSpace : public DiscreteVariableSpaceBase<SimpleDiscreteVariableSpace<NUMBER_OF_LABELS>>{
public:

    SimpleDiscreteVariableSpace(const NVariablesType & n_variables = NVariablesType())
    : n_variables_(n_variables){
    }

    // must have
    auto n_variables()const{
        return this->derived_cast().n_variables();
    }

    auto n_labels(const VariableIndexType i)const{
        return NUMBER_OF_LABELS;
    }
    
     NVariablesType n_variables_;
};


}
}