

#pragma once
#include <cstddef>     // std::size_t 
#include <type_traits> // std::remove_cv
#include <utility>     // std::pair


namespace nifty {
namespace infusion {


template<class DERIVED>
class ConstraintBase{
public:
    typedef DERIVED DerivedType;


    // must have
    auto arity() const{
        return this->derived_cast().arity();
    }
    auto bounds(const std::size_t i)const{
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