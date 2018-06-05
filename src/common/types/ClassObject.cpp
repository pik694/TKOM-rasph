//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "ClassObject.hpp"

#include <common/ast/nodes/class_definition/members/MethodMemberNode.hpp>

rasph::common::types::ClassObject::ClassObject(rasph::interpreter::environment::ClassDefinition &classDefinition)
        : classDefinition_(classDefinition) {}

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
rasph::common::types::ClassObject::valueOfMember(const std::string &name) {

    auto iterator = symbols_.find(name);

    return iterator != symbols_.end() ? iterator->second.getValue().clone() : nullptr ;

}

std::unique_ptr<rasph::common::types::Object>
rasph::common::types::ClassObject::executeMehtod(const std::string &name) {

    auto method =  classDefinition_.getMethod(name);

    if (method == nullptr) throw std::runtime_error("Such a method does not exist");


    //TODO: load symbols

    method->execute();
    auto result = method->result();

    //TODO unload symbols

    return std::move(result);

}



