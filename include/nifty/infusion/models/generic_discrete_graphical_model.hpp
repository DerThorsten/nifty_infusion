#pragma once

#include "nifty/tools/tuple.hpp"
#include "nifty/meta/tuple.hpp"
#include "nifty/infusion/models/factor_index.hpp"
#include "nifty/infusion/models/discrete_graphical_model_base.hpp"
#include "nifty/infusion/factors/function_view_discrete_factor.hpp"


#include <boost/hana.hpp>

#include <cstdint>
#include <iostream>
#include <array>
#include <vector>


namespace nifty {
namespace infusion {





template<class VARIABLE_SPACE, class FUNCTION_TUPLE >
class GenericDiscreteGraphicalModel : 
public DiscreteGraphicalModelBase<GenericDiscreteGraphicalModel<VARIABLE_SPACE, FUNCTION_TUPLE >>{

   
private:

    template<class FUNCTION_TYPE>
    using Factor= FunctionViewDiscreteFactor<FUNCTION_TYPE> ;

    template<class FUNCTION_TYPE>
    using FactorVector = std::vector<Factor<FUNCTION_TYPE>> ;

    template<class FUNCTION_TYPE>
    using FunctionVector = std::vector<FUNCTION_TYPE> ;

    typedef FUNCTION_TUPLE FunctionTuple;
public:
    typedef typename meta::TransformTuple<FunctionTuple, Factor >::type FactorTuple;
private:
    typedef typename meta::TransformTuple<FunctionTuple, FactorVector >::type FactorVectorTuple;
    typedef typename meta::TransformTuple<FunctionTuple, FunctionVector >::type FunctionVectorTuple;



    template<class FUNCTION>
    class FunctionId{
    public:
        FunctionId(const uint64_t index = 0)
        :   index_(index){ 
        }
        auto index()const{
            return index_;
        }
        bool operator<(const FunctionId & other)const{
            return index_ < other.index_;
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

        // find index of function
        typedef meta::TupleTypeIndex<FUNCTION, FunctionTuple> TupleIndex;

        // get the function vector
        auto & vec = std::get<TupleIndex::value>(function_vector_tuple_);

        // index of the function
        const auto f_index = vec.size();

        // add function
        vec.push_back(f);

        // return function identifier 
        return FunctionId<FUNCTION>(f_index);
    }

    template<class FUNCTION, class VI>
    void add_factor(const FunctionId<FUNCTION> & fid, std::initializer_list<VI> vis){



        // find index of function
        typedef meta::TupleTypeIndex<FUNCTION, FunctionTuple> TupleIndex;

        // get the function vector
        const auto & function_vec = std::get<TupleIndex::value>(function_vector_tuple_);

        // get the function
        const auto & function = function_vec[fid.index()];

        // add factor
        std::get<TupleIndex::value>(factor_vector_tuple_).emplace_back(function, vis);

        // update max arity
        max_arity_ = std::max(max_arity_, ArityType(function.arity()));

    }




    template<class FUNCTION, class VI>
    void add_factor(const FUNCTION & function, std::initializer_list<VI> vis){
        // add the function
        const auto fid = this->add_function(function);
        // add factor
        this->add_factor(fid, vis);
    }




    template<std::uint64_t TUPLE_INDEX>
    const auto & operator[](const FactorIndex<TUPLE_INDEX> & factor_index)const{
        return std::get<TUPLE_INDEX>(factor_vector_tuple_)[factor_index.index()];
    }


    template<class F>
    void for_each_factor(F && f)const{

        // loop over each tuple element
        nifty::tools::for_each(factor_vector_tuple_,
         [&](auto && factor_vector) {


            typedef std::decay_t<decltype(factor_vector)> FactorVectorType;
            typedef meta::TupleTypeIndex<FactorVectorType, FactorVectorTuple> TupleIndex;
            typedef FactorIndex<TupleIndex::value> FactorIndexType;

            for(uint64_t i=0; i<factor_vector.size(); ++i){
                f(FactorIndexType(i), factor_vector[i]);
            }

        });
    }

    const auto & variable_space()const{
        return variable_space_;
    }
    
private:
    VariableSpaceType   variable_space_; 
    FunctionVectorTuple function_vector_tuple_;
    FactorVectorTuple   factor_vector_tuple_;
    ArityType max_arity_;
};



} // end namespace nifty::infusion
} // end namespace nifty