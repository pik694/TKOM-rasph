//
// Created by Piotr Żelazko on 08.05.2018.
//

#include "MethodMemberNode.hpp"

using namespace rasph::common::ast::nodes;

void MethodMemberNode::accept(rasph::interpreter::environment::ClassBuilder& builder) {
    builder.addElement(*this);
}

void MethodMemberNode::execute() {

    for(auto& statement: statements_)
        statement->execute();

}

std::unique_ptr<rasph::common::types::Object> MethodMemberNode::result() {
    if (result_)
        return result_->value();
    else return nullptr;
}
