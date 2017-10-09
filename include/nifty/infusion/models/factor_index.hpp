#pragma once


namespace nifty {
namespace infusion {



template<uint64_t TUPLE_INDEX>
class FactorIndex{
public:
    FactorIndex(const uint64_t index = 0)
    :   index_(index){ 
    }
    auto index()const{
        return index_;
    }

    bool operator<(const FactorIndex & other)const{
        return index_ < other.index_;
    }
private:
    uint64_t index_;
};








} // end namespace nifty::infusion
} // end namespace nifty