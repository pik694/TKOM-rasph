//
// Created by Piotr Żelazko on 04.06.2018.
//

#include "ClassDefinition.hpp"

using namespace rasph::interpreter::environment;

const std::string &ClassDefinition::getName() const {
    return name_;
}

ClassDefinition::ClassDefinition(
        ClassDefinition::Name name,
        ClassDefinition::Events events,
        ClassDefinition::Attributes attributes) {

    //TODO
}
