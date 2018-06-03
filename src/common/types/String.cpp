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