//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Symbol.hpp"

using namespace rasph::interpreter::environment::symbols;

Symbol::Symbol(const std::string &name, std::unique_ptr<rasph::common::types::Object> value) : name_(name), value_(std::move(value)) {}

const std::string &Symbol::getName() const {
    return name_;
}

Symbol &Symbol::operator=(Symbol &&symbol) {

    if (name_ != symbol.name_) throw std::invalid_argument("Symbols' names do not equal");

    value_ = std::move(symbol.value_);

    return *this;
}

Symbol::Symbol(Symbol const &other) : name_ (other.name_){

    value_ = other.value_ != nullptr ? other.value_->clone() : nullptr;
}

rasph::common::types::Object const& Symbol::getValue() const {
    return *value_;
}
