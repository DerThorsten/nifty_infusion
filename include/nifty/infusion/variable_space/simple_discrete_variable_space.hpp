#include "nifty/infusion/variable_space/discrete_variable_space_base.hpp"


namespace nifty {
namespace infusion {

template<NLabelsType NUMBER_OF_LABELS, NVariablesType N_VARIABLE = 0>
class SimpleDiscreteVariableSpace;


template<NLabelsType NUMBER_OF_LABELS, NVariablesType N_VARIABLES>
class SimpleDiscreteVariableSpace : 
    public DiscreteVariableSpaceBase<SimpleDiscreteVariableSpace<NUMBER_OF_LABELS,N_VARIABLES>>
{

public:
    // must have
    auto n_variables()const{
        return N_VARIABLES;
    }
    auto n_labels(const VariableIndexType i)const{
        return NUMBER_OF_LABELS;
    }
};


template<NLabelsType NUMBER_OF_LABELS>
class SimpleDiscreteVariableSpace<NUMBER_OF_LABELS,0> : 
    public DiscreteVariableSpaceBase<SimpleDiscreteVariableSpace<NUMBER_OF_LABELS,0>>
{

public:
    SimpleDiscreteVariableSpace(const NVariablesType & n_variables = NVariablesType())
    : n_variables_(n_variables){
    }

    // must have
    auto n_variables()const{
        return n_variables_;
    }

    auto n_labels(const VariableIndexType i)const{
        return NUMBER_OF_LABELS;
    }
private:
    NVariablesType n_variables_;
};

template<>
class SimpleDiscreteVariableSpace<0,0> : 
    public DiscreteVariableSpaceBase<SimpleDiscreteVariableSpace<0,0>>
{

public:
    SimpleDiscreteVariableSpace(
        const NVariablesType & n_variables = NVariablesType(),
        const NLabelsType & n_labels = 2
    )
    :   n_variables_(n_variables),
        n_labels_(n_labels)
    {

    }

    // must have
    auto n_variables()const{
        return n_variables_;
    }

    auto n_labels(const VariableIndexType i)const{
        return n_labels_;
    }
private:
    NVariablesType n_variables_;
    NLabelsType n_labels_;
};



}
}