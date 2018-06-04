//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "String.hpp"

rasph::common::types::String::String(const std::string &value) : value_(value) {}

const std::string &rasph::common::types::String::getValue() const {
    return value_;
}

void rasph::common::types::String::setValue(const std::string &value_) {
    String::value_ = value_;
}

rasph::common::types::String::operator bool() const {
    return value_.size() == 0;
}

bool rasph::common::types::String::operator!() const {
    return !bool();
}

rasph::common::types::String *rasph::common::types::String::copyImplementation() const {
    return new String(*this);
}

std::unique_ptr<rasph::common::types::String> rasph::common::types::String::clone() const {
    return std::unique_ptr<String>(this->copyImplementation());
}
