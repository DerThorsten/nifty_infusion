#include "nifty/infusion/variable_space/variable_space_base.hpp"

namespace nifty {
namespace infusion {




template<class DERIVED>
class DiscreteVariableSpaceBase : public VariableSpaceBase<DERIVED>{
public:
    typedef DERIVED DerivedType;


    // must have
    auto n_variables()const{
        return this->derived_cast().n_variables();
    }

    auto n_labels(const VariableIndexType i)const{
        return this->derived_cast().n_labels(i);
    }
    auto bounds(const VariableIndexType i)const{
        const auto nl = this->derived_cast().n_labels(i);
        typedef typename std::remove_cv<decltype(nl)>::type NLabelsType;
        return std::make_pair(static_cast<NLabelsType>(0),nl-1);
    }

};


}
}