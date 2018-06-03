//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Symbol.hpp"

using namespace rasph::interpreter::environment::symbols;

Symbol::Symbol(const std::string &name) : name_(name) {}

const std::string &Symbol::getName() const {
    return name_;
}


Symbol::~Symbol() {}
