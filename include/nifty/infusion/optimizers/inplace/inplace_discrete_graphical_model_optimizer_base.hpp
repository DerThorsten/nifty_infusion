#pragma once


namespace nifty {
namespace infusion {
    

    template<class DERIVED>
    class InplaceDiscreteGraphicalModelOptimzerBase{
    public:
        typedef DERIVED DerivedType;


        // must have
        auto variable_space() const {
            return this->derived_cast().variable_space();
        }

        auto state(const VariableIndexType vi) const {
            return this->derived_cast().state(vi);
        }

        




        


        // optimality
        bool is_optimal()const{
            return false;
        }


        // partial optimality
        bool is_partial_optimal(const VariableIndexType vi) const {

            return this->derived_cast().is_optimal() ? 
                true : false;
        }

        // bool could_be_optimal(const VariableIndexType vi, const DiscreteLabelType state)const{
        //     if(this->derived_cast().is_optimal())
        //         return this->derived_cast().state(vi) == state ? true : false;
        //     else
        //         return true;
        // }

        





        





        DerivedType & derived_cast(){
            return static_cast<DerivedType &>(*this);
        }
        const DerivedType & derived_cast() const {
            return static_cast<const DerivedType &>(*this);
        }   





    };

}
}