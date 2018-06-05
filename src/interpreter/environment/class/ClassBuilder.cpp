//
// Created by Piotr Żelazko on 04.06.2018.
//

#include "ClassBuilder.hpp"
#include <common/ast/nodes/class_definition/ClassNode.hpp>
#include <common/ast/nodes/class_definition/members/AttributeMemberNode.hpp>
#include <common/ast/nodes/class_definition/members/EventMemberNode.hpp>
#include <common/ast/nodes/class_definition/members/MethodMemberNode.hpp>
#include <interpreter/environment/SymbolManager.hpp>

void rasph::interpreter::environment::ClassBuilder::build(const rasph::common::ast::nodes::ClassNode &classNode) {

    name_ = classNode.getName();

    if (SymbolManager::getInstance().contains(name_))
        throw std::runtime_error("Class redefinition: " + classNode.getName());

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
//
//    if (methods_.find(node.getName()) != methods_.end())
//        throw std::runtime_error("Duplicate function with name: " + node.getName());

    auto &ref = const_cast<rasph::common::ast::nodes::MethodMemberNode &>(node);
    auto *ptr = new rasph::common::ast::nodes::MethodMemberNode(std::move(ref));

    auto pair = std::make_pair(node.getName(), ptr);

    methods_.push_back(pair);


}


void rasph::interpreter::environment::ClassBuilder::compose() {

    std::unordered_map<std::string, rasph::common::ast::nodes::MethodMemberNode*> map;

    for(auto& pair : methods_){
        if (!map.insert(std::move(pair)).second){
            throw std::runtime_error("Duplicate method");
        }
    }

    auto classDefinition = std::unique_ptr<common::types::Object>(new ClassDefinition(ClassDefinition::Name(name_),
                                                                                      ClassDefinition::Events(events_),
                                                                                      ClassDefinition::Attributes(
                                                                                              attributes_),
                                                                                      ClassDefinition::Methods(map)
    ));


    symbols::Symbol symbol(name_, std::move(classDefinition));

    SymbolManager::getInstance().saveSymbol(std::move(symbol));


}


