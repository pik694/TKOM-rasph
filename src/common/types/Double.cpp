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


rasph::common::types::Double::operator bool() const {
    return value_ != 0.0;
}

bool rasph::common::types::Double::operator!() const {
    return !bool();
}

rasph::common::types::Double *rasph::common::types::Double::copyImplementation() const {
    return new Double(*this);
}

std::unique_ptr<rasph::common::types::Double> rasph::common::types::Double::clone() const {
    return std::unique_ptr<Double>(this->copyImplementation());

}

bool rasph::common::types::Double::operator<(rasph::common::types::Object &object) const {
    return false;
}

bool rasph::common::types::Double::operator>(rasph::common::types::Object &object) const {
    return false;
}

bool rasph::common::types::Double::operator<=(rasph::common::types::Object &object) const {
    return false;
}

bool rasph::common::types::Double::operator>=(rasph::common::types::Object &object) const {
    return false;
}
