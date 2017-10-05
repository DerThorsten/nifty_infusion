#pragma once

#include "nifty/infusion/models/discrete_graphical_model_base.hpp"
#include "nifty/infusion/factors/function_view_discrete_factor.hpp"


#include <boost/hana.hpp>

#include <cstdint>
#include <iostream>
#include <array>
#include <vector>


#include <boost/hana.hpp>





namespace nifty {
namespace infusion {


template <typename Iterable, typename T>
constexpr auto index_of(const Iterable & iterable,  const T & element) {
    auto size = decltype(boost::hana::size(iterable)){};
    auto dropped = decltype(boost::hana::size(
        boost::hana::drop_while(iterable, boost::hana::not_equal.to(element))
    )){};
    return size - dropped;
}



template <typename TUPLE>
constexpr auto tovec(const TUPLE & tuple) { 
    return boost::hana::transform(tuple, [](auto t) {
        return boost::hana::type_c<std::vector<typename decltype(t)::type>>;
    });
}

template<class T>
struct FactorHelper;

template<class  ... FUNCTION_TYPES>
struct FactorHelper<std::tuple<FUNCTION_TYPES ...> >{

    template<class FUNCTION_TYPE>
    using Factor= FunctionViewDiscreteFactor<FUNCTION_TYPE> ;

    template<class FUNCTION_TYPE>
    using FactorVector = std::vector<Factor<FUNCTION_TYPE>> ;

    template<class FUNCTION_TYPE>
    using FunctionVector = std::vector<FUNCTION_TYPE> ;


    typedef boost::hana::tuple< Factor<FUNCTION_TYPES> ...>         FactorTuple;
    typedef boost::hana::tuple< FactorVector<FUNCTION_TYPES> ...>   FactorVectorTuple;
    typedef boost::hana::tuple< FunctionVector<FUNCTION_TYPES> ...> FunctionVectorTuple;

    static constexpr auto factorTupleT = boost::hana::tuple_t< Factor<FUNCTION_TYPES> ...> ;
    static constexpr auto factorVectorTupleT = boost::hana::tuple_t< FactorVector<FUNCTION_TYPES> ...> ;
    static constexpr auto functionVectorTupleT = boost::hana::tuple_t< FunctionVector<FUNCTION_TYPES> ...> ;
};


template<class VARIABLE_SPACE, class FUNCTION_TYPES_TUPLE >
class GenericDiscreteGraphicalModel : 
public DiscreteGraphicalModelBase<GenericDiscreteGraphicalModel<VARIABLE_SPACE, FUNCTION_TYPES_TUPLE >>{

   
private:



    typedef  FactorHelper<FUNCTION_TYPES_TUPLE> FactorHelperType;






    typedef typename FactorHelperType::FactorTuple FactorTuple;
    typedef typename FactorHelperType::FactorVectorTuple FactorVectorTuple;
    typedef typename FactorHelperType::FunctionVectorTuple FunctionVectorTuple;


    template<class FUNCTION>
    class FunctionId{
    public:
        FunctionId(const uint64_t index = 0)
        :   index_(index){ 
        }
        auto index()const{
            return index_;
        }
    private:
        uint64_t index_;
    };

public:
    typedef VARIABLE_SPACE VariableSpaceType;


    template<class ... ARGS>
    GenericDiscreteGraphicalModel(ARGS && ... args)
    :   variable_space_(std::forward<ARGS>(args)...),
        function_vector_tuple_(),
        factor_vector_tuple_(),
        max_arity_(0)
    {

    }

    auto max_arity()const{
        return max_arity_;
    }

    template<class FUNCTION>
    auto add_function(const FUNCTION & f){

        auto t = FactorHelperType::functionVectorTupleT;
        constexpr auto index = index_of(t, boost::hana::type_c< typename FactorHelperType:: template FunctionVector<FUNCTION> >);
        const auto i = boost::hana::at(function_vector_tuple_, index).size();
        boost::hana::at(function_vector_tuple_, index).push_back(f);
        return FunctionId<FUNCTION>(i);
    }

    template<class FUNCTION, class VI>
    void add_factor(const FunctionId<FUNCTION> & fid, std::initializer_list<VI> vis){
        auto t = FactorHelperType::functionVectorTupleT;
        constexpr auto index = index_of(t, boost::hana::type_c< typename FactorHelperType:: template FunctionVector<FUNCTION> >);
        const auto & vec = boost::hana::at(function_vector_tuple_, index);
        const auto & function_ref = vec[fid.index()];
        boost::hana::at(factor_vector_tuple_, index).emplace_back(function_ref, vis);
        max_arity_ = std::max(max_arity_, ArityType(function_ref.arity()));
    }


    template<class FUNCTION, class VI>
    void add_factor(const FUNCTION & function, std::initializer_list<VI> vis){
        // add the function
        const auto fid = this->add_function(function);
        // add factor
        this->add_factor(fid, vis);
    }



    template<class F>
    void for_each_factor(F && f)const{
        boost::hana::for_each(factor_vector_tuple_, [&](auto && factor_vector) {
            for(const auto & factor : factor_vector){
                f(factor);
            }
        });
    }


    
private:
    VariableSpaceType   variable_space_; 
    FunctionVectorTuple function_vector_tuple_;
    FactorVectorTuple   factor_vector_tuple_;
    ArityType max_arity_;
};



} // end namespace nifty::infusion
} // end namespace nifty