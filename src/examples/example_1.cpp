#include "nifty/infusion/infusion.hpp"
#include "nifty/infusion/functions/discrete_function_base.hpp"


#include <iostream>
#include <array>
#include <vector>

#include <boost/hana.hpp>


namespace hana = boost::hana;


namespace nifty {
namespace infusion {


template <typename Iterable, typename T>
constexpr auto index_of(const Iterable & iterable,  const T & element) {
    auto size = decltype(hana::size(iterable)){};
    auto dropped = decltype(hana::size(
        hana::drop_while(iterable, hana::not_equal.to(element))
    )){};
    return size - dropped;
}



template<NLabelsType N_LABELS>
struct UnariesN
:   public DiscreteFunctionBase<UnariesN<N_LABELS>>
{
    constexpr auto n_labels(std::size_t i)const{
        return N_LABELS;
    }
    constexpr auto arity()const{
        return 1;
    }
    template<class LABELS>
    auto eval(const LABELS & labels){
        return data_[labels[0]];
    }
    std::array<float, N_LABELS> data_;
};

template<ArityType N_LABELS>
struct StaticPropertyArity<UnariesN<N_LABELS>>
: public StaticArity<1>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<UnariesN<N_LABELS>>
: public StaticShape<N_LABELS>{
};



template<std::size_t N_LABELS>
struct PottsN
:   public DiscreteFunctionBase<PottsN<N_LABELS>>
{
    constexpr auto n_labels(std::size_t i)const{
        return N_LABELS;
    }
    constexpr auto arity()const{
        return 2;
    }
    template<class LABELS>
    auto eval(const LABELS & labels){
        return labels[0] != labels[1] ? beta_ : 0.0f;
    }
    float beta_;
};


template<ArityType N_LABELS>
struct StaticPropertyArity<PottsN<N_LABELS>>
: public StaticArity<2>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyShape<PottsN<N_LABELS>>
: public StaticShape<N_LABELS, N_LABELS>{
};

template<NLabelsType N_LABELS>
struct StaticPropertyIsPotts<PottsN<N_LABELS>>
: public std::true_type{
};





template<class FUNCTION>
struct Factor{
    FUNCTION                   function_;
    std::vector<std::size_t>   variables_;
};


template<class ... FUNCTION_TYPES>
class Gm{
public:





    template<class FUNCTION>
    using FacVec = std::vector<Factor<FUNCTION>>;

    // types
    typedef boost::hana::tuple< FacVec<FUNCTION_TYPES> ...> Factors;

    template<class FUNCTION>
    void add_factor(const FUNCTION & f){

        Factor<FUNCTION> factor;
        factor.function_ = f;

        auto t = boost::hana::tuple_t< FacVec<FUNCTION_TYPES> ...>;
        constexpr auto index = index_of(t, hana::type_c< FacVec<FUNCTION> >);
        hana::at(factors_, index).push_back(factor);
    }



    template<class F>
    void for_each_factor(F && f)const{
        hana::for_each(factors_, [&](auto && factor_vector) {
            for(const auto & factor : factor_vector){
                f(factor);
            }
        });
    }


    Factors factors_;
};


}
}



int main(){
    using namespace nifty::infusion;

    auto t = boost::hana::tuple_t<int*, char&, void>;
    typedef Gm<UnariesN<2>, PottsN<2> > GmType;

    GmType gm;


    PottsN<2> potts;
    potts.beta_ = 1.0;

    UnariesN<2> unaries;
    unaries.data_[0] = 1.0;
    unaries.data_[1] = 2.0; 

    gm.add_factor(potts);
    gm.add_factor(unaries);



    gm.for_each_factor(

    [&](auto && factor){
        std::cout<<factor.function_.arity()<<"\n";
        std::cout<<factor.function_.bounds(0).first<<"\n";
    }

    );

}