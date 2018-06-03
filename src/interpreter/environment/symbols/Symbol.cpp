//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Symbol.hpp"

using namespace rasph::interpreter::environment::symbols;

Symbol::Symbol(const std::string &name) : name_(name) {}

const std::string &Symbol::getName() const {
    return name_;
}

Symbol &Symbol::operator=(Symbol &&symbol) {

    if (name_ != symbol.name_) throw std::invalid_argument("Symbols' names do not equal");

    //TODO

    return *this;
}

Symbol::Symbol(Symbol const &other) :name_ (other.name_){}
