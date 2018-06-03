//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Boolean.hpp"

rasph::common::types::Boolean::Boolean(bool value) : value_(value) {}

bool rasph::common::types::Boolean::getValue() const {
    return value_;
}

void rasph::common::types::Boolean::setValue(bool value_) {
    this->value_ = value_;
}
