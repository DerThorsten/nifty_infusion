#pragma once
#include <cstddef>     // std::size_t 


#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <vector>

#include "nifty/infusion/static_properties.hpp"
#include "nifty/infusion/functions/value_functions/value_function_base.hpp"

namespace nifty {
namespace infusion {


template<class DERIVED>
class DiscreteValueFunctionBase : public ValueFunctionBase<DERIVED>{
public:
    typedef DERIVED DerivedType;
    auto n_labels(const std::size_t i)const{
        return this->derived_cast().n_labels(i);
    }

    auto shape(const std::size_t i)const{
        return this->derived_cast().n_labels(i);
    }

    auto bounds(const std::size_t i)const{
        const auto nl = this->derived_cast().n_labels(i);
        typedef typename std::remove_cv<decltype(nl)>::type NLabelsType;
        return std::make_pair(static_cast<NLabelsType>(0),nl-1);
    }

    auto operator()(const DiscreteLabelType l0)const{
        return this->derived_cast().operator()(&l0);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1)const{
        const DiscreteLabelType l[2] = {l0, l1};
        return this->derived_cast().operator()(l);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1, 
                    const DiscreteLabelType l2)const{
        const DiscreteLabelType l[3] = {l0, l1, l2};
        return this->derived_cast().operator()(l);
    }

    auto operator()(const DiscreteLabelType l0, const DiscreteLabelType l1, 
                    const DiscreteLabelType l2, const DiscreteLabelType l3)const{
        const DiscreteLabelType l[4] = {l0, l1, l2, l3};
        return this->derived_cast().operator()(l);
    }
    

    template<class BUFFER_TYPE>
    void c_order_buffer(std::vector<BUFFER_TYPE> & buffer )const{

        const auto derived = this->derived_cast();
        const auto dim = derived.arity();
        const auto size = derived.size();

        if(buffer.size()<size)
            buffer.resize(size);

        switch(dim){
            case 1:{
                for(auto x0=0; x0<derived.shape(0); ++x0){
                    buffer[x0] = derived(x0);
                }
                break;
            }
            case 2:{
                auto i = 0;
                for(auto x0=0; x0<derived.shape(0); ++x0)
                for(auto x1=0; x1<derived.shape(1); ++x1){
                    buffer[i] = derived(x0, x1);
                    ++i;
                }
                break;
            }
            case 3:{
                auto i = 0;
                for(auto x0=0; x0<derived.shape(0); ++x0)
                for(auto x1=0; x1<derived.shape(1); ++x1)
                for(auto x2=0; x2<derived.shape(2); ++x2){
                    buffer[i] = derived(x0, x1, x2);
                    ++i;
                }
                break;
            }
            case 4:{
                auto i = 0;
                for(auto x0=0; x0<derived.shape(0); ++x0)
                for(auto x1=0; x1<derived.shape(1); ++x1)
                for(auto x2=0; x2<derived.shape(2); ++x2)
                for(auto x3=0; x3<derived.shape(3); ++x3){
                    buffer[i] = derived(x0, x1, x2, x3);
                    ++i;
                }
                break;
            }
            case 5:{
                throw std::runtime_error("not yet implemented");
            }
        }
    }

    template<class BUFFER_TYPE>
    void f_order_buffer(std::vector<BUFFER_TYPE> & buffer )const{

        const auto derived = this->derived_cast();
        const auto dim = derived.arity();
        const auto size = derived.size();

        if(buffer.size()<size)
            buffer.resize(size);

        switch(dim){
            case 1:{
                for(auto x0=0; x0<derived.shape(0); ++x0){
                    buffer[x0] = derived(x0);
                }
                break;
            }
            case 2:{
                auto i = 0;
                for(auto x1=0; x1<derived.shape(1); ++x1)
                for(auto x0=0; x0<derived.shape(0); ++x0){
                    buffer[i] = derived(x0, x1);
                    ++i;
                }
                break;
            }
            case 3:{
                auto i = 0;
                for(auto x2=0; x2<derived.shape(2); ++x2)
                for(auto x1=0; x1<derived.shape(1); ++x1)
                for(auto x0=0; x0<derived.shape(0); ++x0){
                    buffer[i] = derived(x0, x1, x2);
                    ++i;
                }
                break;
            }
            case 4:{
                auto i = 0;
                for(auto x3=0; x3<derived.shape(3); ++x3)
                for(auto x2=0; x2<derived.shape(2); ++x2)
                for(auto x1=0; x1<derived.shape(1); ++x1)
                for(auto x0=0; x0<derived.shape(0); ++x0){
                    buffer[i] = derived(x0, x1, x2, x3);
                    ++i;
                }
                break;
            }
            case 5:{
                throw std::runtime_error("not yet implemented");
            }
        }
    }
};


}
}