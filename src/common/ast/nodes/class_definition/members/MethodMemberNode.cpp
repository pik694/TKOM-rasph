//
// Created by Piotr Żelazko on 08.05.2018.
//

#include "MethodMemberNode.hpp"

using namespace rasph::common::ast::nodes;

void MethodMemberNode::accept(rasph::interpreter::environment::ClassBuilder& builder) {
    builder.addElement(*this);
}
