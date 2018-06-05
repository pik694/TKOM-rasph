//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "ClassObject.hpp"

#include <common/ast/nodes/class_definition/members/MethodMemberNode.hpp>
#include <interpreter/environment/SymbolManager.hpp>

rasph::common::types::ClassObject::ClassObject(const rasph::interpreter::environment::ClassDefinition &classDefinition)
        : classDefinition_(classDefinition) {

    auto& attributes = classDefinition.getAttributes();

    for (auto const& member : attributes){
        symbols_.insert(std::make_pair(member, interpreter::environment::symbols::Symbol(member, nullptr)));
    }

}

rasph::common::types::ClassObject::operator bool() const {
    return false;
}

bool rasph::common::types::ClassObject::operator!() const {
    return false;
}

bool rasph::common::types::ClassObject::operator==(const rasph::common::types::Object &object) const {
    return false;
}

bool rasph::common::types::ClassObject::operator<(const rasph::common::types::Object &object) const {
    return false;
}

bool rasph::common::types::ClassObject::operator>(const rasph::common::types::Object &object) const {
    return false;
}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::accept(const rasph::common::types::visitors::AddVisitor &visitor) const {
    throw std::runtime_error("Invalid argument type");
}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::accept(const rasph::common::types::visitors::SubtractVisitor &visitor) const {
    throw std::runtime_error("Invalid argument type");
}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::accept(const rasph::common::types::visitors::MultiplyVisitor &visitor) const {
    throw std::runtime_error("Invalid argument type");
}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::accept(const rasph::common::types::visitors::DivideVisitor &visitor) const {
    throw std::runtime_error("Invalid argument type");
}

rasph::common::types::Object *rasph::common::types::ClassObject::copyImplementation() const {
    return new ClassObject(*this);
}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::valueOfMember(const std::string &name) const {

    auto iterator = symbols_.find(name);

    return iterator != symbols_.end() ? iterator->second.getValue().clone() : nullptr ;

}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::executeMehtod(const std::string &name) {

    auto method =  classDefinition_.getMethod(name);

    if (method == nullptr) throw std::runtime_error("Such a method does not exist");


    interpreter::environment::SymbolManager::getInstance().setClassMembers(&symbols_);

    method->execute();
    auto result = method->result();

    interpreter::environment::SymbolManager::getInstance().unsetClassMembers() ;

    return std::move(result);

}



