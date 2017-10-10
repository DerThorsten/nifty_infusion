#pragma once

#include <boost/container/flat_set.hpp>


namespace nifty {
namespace infusion {













        namespace detail_infusion{
            template<uint64_t TUPLE_INDEX>
            using FlatFactorIndexSet = boost::container::flat_set<FactorIndex<TUPLE_INDEX>>;
        }






        template<class GM>
        class HeterogeneousFlatFactorIndexSet
        :   public meta::GenerateTuple<
                std::tuple_size<typename GM::FactorTuple>::value,
                detail_infusion::FlatFactorIndexSet
            >::type
        {
        public:
            template<uint64_t TUPLE_INDEX>
            void insert(const FactorIndex<TUPLE_INDEX> & index){
                std::get<TUPLE_INDEX>(*this).insert(index);
            }

            template<class F>
            void for_each(F && f)const{
                // loop over each tuple element
                nifty::tools::for_each(*this,[&](auto && factor_index_set) {
                    for(const auto & factor_index : factor_index_set){
                        f(factor_index);
                    }
                });
            }
        };





}
}