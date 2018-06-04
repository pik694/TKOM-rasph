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

        explicit operator bool() const override;

        std::unique_ptr<Double> clone () const;

        bool operator!() const override;

    private:

        Double *copyImplementation() const override;

        double value_;
    };
}


#endif //RASPH_DOUBLE_HPP
