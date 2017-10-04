

#include "doctest.h"

#include <iostream>

#include <array>
#include <boost/hana.hpp>

namespace hana = boost::hana;



template<std::size_t N_LABELS>
struct UnariesN{
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



struct PottsN{
    constexpr auto n_labels(std::size_t i)const{
        return 2;
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



template<class ... FUNCTIONS>
class Gm{
public:

};





TEST_CASE("infusion externals ") {


    // types
    auto types = hana::tuple_t<int*, char&, void>;

    auto ts = hana::filter(types, [](auto t) {
        return hana::traits::is_pointer(t) || hana::traits::is_reference(t);
    });

    // values
    auto values = hana::make_tuple(1, 'c', 3.5);

    auto vs = hana::filter(values, [](auto const& t) {
      return hana::traits::is_integral(hana::typeid_(t));
    });


    hana::for_each(values, [](auto const& element) {
        std::cout << element << std::endl;
    });

}