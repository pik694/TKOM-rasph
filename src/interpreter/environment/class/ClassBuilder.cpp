//
// Created by Piotr Żelazko on 04.06.2018.
//

#include "ClassBuilder.hpp"
#include <common/ast/nodes/class_definition/ClassNode.hpp>
#include <common/ast/nodes/class_definition/members/AttributeMemberNode.hpp>
#include <common/ast/nodes/class_definition/members/EventMemberNode.hpp>
#include <common/ast/nodes/class_definition/members/MethodMemberNode.hpp>

void rasph::interpreter::environment::ClassBuilder::build(const rasph::common::ast::nodes::ClassNode &classNode) {

    //TODO: check name

    name_ = classNode.getName();

    auto const &members = classNode.getMembers();

    for (auto &member : members) {
        member->accept(*this);
    }

    compose();

}

void
rasph::interpreter::environment::ClassBuilder::addElement(const rasph::common::ast::nodes::AttributeMemberNode &node) {

    attributes_.push_back(node.getName());

}

void rasph::interpreter::environment::ClassBuilder::addElement(const rasph::common::ast::nodes::EventMemberNode &node) {
    events_.push_back(node.getName());
}

void
rasph::interpreter::environment::ClassBuilder::addElement(const rasph::common::ast::nodes::MethodMemberNode &node) {

    if (methods_.find(node.getName()) != methods_.end()) throw std::runtime_error("Duplicate function with name: " + node.getName());

    auto& ref = const_cast<rasph::common::ast::nodes::MethodMemberNode&>(node);
    auto* ptr = new rasph::common::ast::nodes::MethodMemberNode(std::move(ref));

    methods_.insert(std::make_pair(node.getName(), ptr));

}


void rasph::interpreter::environment::ClassBuilder::compose() {

    auto classDefinition = std::make_unique<ClassDefinition>(ClassDefinition::Name(name_),
                                                             ClassDefinition::Events(events_),
                                                             ClassDefinition::Attributes(attributes_));




}

rasph::interpreter::environment::ClassBuilder::~ClassBuilder() {
    for (auto pair : methods_){
        delete pair.second;
    }

}
