#pragma once

#include <cstddef>     // std::size_t 
#include <type_traits> // std::remove_cv
#include <utility>     // std::pair


namespace nifty {
namespace infusion {


template<class DERIVED>
class FunctionBase{
public:
    typedef DERIVED DerivedType;


    // must have
    auto arity() const{
        return this->derived_cast().arity();
    }
    auto bounds(const std::size_t i)const{
        return this->derived_cast().bounds(i);   
    }
    template<class LABELS>
    auto operator()(const LABELS & labels)const{
        return this->derived_cast().operator()(labels);   
    }



   //auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1)const{
   //    std::array<DiscreteLabelType, 2> l{ {l0, l1} };
   //    return this->derived_cast().operator()(l);
   //}

    // template<class ARGS ..., typename std::enable_if<std::is_arithmetic<T>::value ,int>::type >
    // auto operator(const ARGS & args)const{
    //     std::initializer_list<ARGS
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