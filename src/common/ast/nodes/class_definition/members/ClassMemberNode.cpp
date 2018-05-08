//
// Created by Piotr Żelazko on 07.05.2018.
//

#include "ClassMemberNode.hpp"

rasph::common::ast::nodes::ClassMemberNode::ClassMemberNode(const std::string &name) : name_(name) {}

const std::string &rasph::common::ast::nodes::ClassMemberNode::getName() const {
    return name_;
}
