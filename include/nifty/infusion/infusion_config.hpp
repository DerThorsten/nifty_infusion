#pragma once

#include <cstdint>

#define NIFTY_INFUSION_VERSION_MAJOR 0
#define NIFTY_INFUSION_VERSION_MINOR 1
#define NIFTY_INFUSION_VERSION_PATCH 0

// DETECT 3.6 <= clang < 3.8 for compiler bug workaround.
//  from  https://github.com/QuantStack/xtensor/blob/master/include/xtensor/xtensor_config.hpp
#ifdef __clang__
    #if __clang_major__ == 3 && __clang_minor__ < 8
        #define NIFTY_INFUSION_OLD_CLANG
    #endif
#endif




namespace nifty {
namespace infusion {

typedef std::uint64_t     DiscreteLabelType;
typedef std::uint64_t     VariableIndexType;
typedef std::uint64_t     ArityType;
typedef DiscreteLabelType NLabelsType;
typedef VariableIndexType NVariablesType;
struct NoneType{};


}
}