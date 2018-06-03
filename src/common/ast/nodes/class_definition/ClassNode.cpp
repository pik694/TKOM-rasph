//
// Created by Piotr Żelazko on 07.05.2018.
//

#include "ClassNode.hpp"

using namespace rasph::common::ast::nodes;

rasph::common::ast::nodes::ClassNode::ClassNode(const std::string &name) : name_(name) {}

const std::string &ClassNode::getName() const {
    return name_;
}

void ClassNode::addNode(std::unique_ptr<ClassMemberNode> member) {
    members_.push_back(std::move(member));
}

const std::vector<std::unique_ptr<ClassMemberNode>> &ClassNode::getMembers() const {
    return members_;
}

void ClassNode::execute() {
    build();
}

void ClassNode::build() {
    //TODO
    throw std::runtime_error("TOOD");
}
