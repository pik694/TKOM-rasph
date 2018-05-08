//
// Created by Piotr Żelazko on 08.05.2018.
//

#include "MethodMemberNode.hpp"

rasph::common::ast::nodes::MethodMemberNode::MethodMemberNode(const std::string &name) : ClassMemberNode(name) {}

const std::vector<std::unique_ptr<int>> &rasph::common::ast::nodes::MethodMemberNode::getParameters() const {
    return parameters_;
}

const std::list<std::unique_ptr<int>> &rasph::common::ast::nodes::MethodMemberNode::getStatements() const {
    return statements_;
}
