//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_BOOLEAN_HPP
#define RASPH_BOOLEAN_HPP

#include "Object.hpp"

namespace rasph::common::types {
    class Boolean : public Object {
    public:
        Boolean(bool value);

        bool getValue() const;

        void setValue(bool value_);

        explicit operator bool() const override;

        std::unique_ptr<Boolean> clone() const;

        bool operator!() const override;

    private:
        Boolean *copyImplementation() const override;

    private:
        bool value_;
    };
}


#endif //RASPH_BOOLEAN_HPP
