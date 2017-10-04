#pragma once


namespace nifty {
namespace infusion {







template<class DERIVED>
class ModelBase{
public:
    typedef DERIVED DerivedType;



    // must have
    auto n_variables() const {
        
    }



    DerivedType & derived_cast(){
        return static_cast<DerivedType &>(*this);
    }
    const DerivedType & derived_cast() const {
        return static_cast<const DerivedType &>(*this);
    }
};

} // end namespace nifty::infusion
} // end namespace nifty
