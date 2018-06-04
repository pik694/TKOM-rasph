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

rasph::common::types::Boolean::operator bool() const {
    return value_;
}

bool rasph::common::types::Boolean::operator!() const {
    return !value_;
}

rasph::common::types::Boolean *rasph::common::types::Boolean::copyImplementation() const {
    return new Boolean(*this);
}

std::unique_ptr<rasph::common::types::Boolean> rasph::common::types::Boolean::clone() const {
    return std::unique_ptr<Boolean>(this->copyImplementation());

}
