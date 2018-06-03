//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Double.hpp"

rasph::common::types::Double::Double(double value) : value_(value) {}

double rasph::common::types::Double::getValue() const {
    return value_;
}

void rasph::common::types::Double::setValue(double value_) {
    Double::value_ = value_;
}
