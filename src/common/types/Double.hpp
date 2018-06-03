//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_DOUBLE_HPP
#define RASPH_DOUBLE_HPP

#include "Object.hpp"

namespace rasph::common::types {
    class Double : public Object {
    public:
        Double(double value);

        double getValue() const;

        void setValue(double value_);

    private:
        double value_;
    };
}


#endif //RASPH_DOUBLE_HPP
