#include "doctest.h"

#include "nifty/infusion/functions/value_functions/potts_function.hpp"


TEST_CASE("potts-function") {
    using namespace  nifty::infusion;
    auto f =PottsFunction<2>( 1.0);
    auto v00 = f(0,0);
    auto v01 = f(0,1);
}