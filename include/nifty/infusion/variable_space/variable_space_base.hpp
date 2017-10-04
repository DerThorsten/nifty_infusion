

namespace nifty {
namespace infusion {




template<class DERIVED>
class VariableSpaceBase{
public:
    typedef DERIVED DerivedType;


    // must have
    auto n_variables()const{
        return this->derived_cast().n_variables();
    }
    auto bounds(const VariableIndexType i)const{
        return this->derived_cast().bounds(i);   
    }
    

    DerivedType & derived_cast(){
        return static_cast<DerivedType &>(*this);
    }
    const DerivedType & derived_cast() const {
        return static_cast<const DerivedType &>(*this);
    }
};


}
}