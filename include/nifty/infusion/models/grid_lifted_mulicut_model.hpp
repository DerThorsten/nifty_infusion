#pragma once

#include "nifty/infusion/models/model_base.hpp"

namespace nifty {
namespace infusion {




template<class T, std::size_t DIM>
class GridLiftedMulticutModel;


template<class T>
class GridLiftedMulticutModel<T, 2>
{
public:
    const static std::size_t DIM = 2;
    typedef std::array<int32_t > ShapeType;
    typedef ShapeType CoordinateType;
    typedef CoordinateType OffsetType;
    typedef std::vector<OffsetType> OffsetVector;
    typedef xt::xtensor<T, DIM + 1> WeightsTensor;
    typedef T WeightType;


    template<class D>
    GridLiftedMulticutModel(
        const xt::xexpression<D> & weights
        const OffsetVector & offsets_vector
    )
    :   shape_(),
        offsets_vector_(offset_vector),
        weights_(weights)
    {
        // copy spatial shape
        const auto & weights_shape = weights_.shape();
        std::copy(weights_shape.begin(), weights_shape.begin()+DIM, shape_);
    }



    template<class D>
    WeightType eval(
        const xt::xexpression<D> & labels
    ){
        WeightType sum = 0;

        const auto n_offsets = offsets_vector_.size();

        for(int p0=0; p0<shape_[0]; ++p0)
        for(int p1=0; p1<shape_[1]; ++p1){

            // todo: speedup access
            const auto lu = labels(p0, p1);

            for(int offset_index=0; offset_index<n_offsets; ++offset_index){
                const auto & offset = offsets_vector_[offset_index];

                // the coordinates of the node u pixel
                const auto q0 = p0 + offset[0];
                const auto q1 = p1 + offset[1];

                // check if inside
                if(q0 >=0 &&  q1 >=0 && q0 <shape_[0] && q1 <shape_[1]){
                    
                    const auto lv = labels(q0, q1);
                    if(lu != lv){

                        // todo: speedup access
                        sum += weights_(p0, p1, offset_index);
                    }
                }                
            }
        }
        
        return sum;
    }



private:
    ShapeType               shape_:
    OffsetVector            offsets_vector_;
    WeightsTensor           weights_;
};


} // end namespace nifty::infusion
} // end namespace nifty
