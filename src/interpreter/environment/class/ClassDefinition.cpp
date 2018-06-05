//
// Created by Piotr Żelazko on 04.06.2018.
//

#include "ClassDefinition.hpp"
#include "common/types/ClassObject.hpp"

using namespace rasph::interpreter::environment;

const std::string &ClassDefinition::getName() const {
    return name_;
}

ClassDefinition::ClassDefinition(
        ClassDefinition::Name name,
        ClassDefinition::Events events,
        ClassDefinition::Attributes attributes,
        ClassDefinition::Methods methods
):
name_(std::move(name.get())),
attributes_(std::move(attributes.get())),
events_(std::move(events.get())),
methods_(std::move(methods.get()))
{
}

ClassDefinition::operator bool() const {
    return false;
}

bool ClassDefinition::operator!() const {
    return false;
}

bool ClassDefinition::operator==(const rasph::common::types::Object &object) const {
    return false;
}

bool ClassDefinition::operator<(const rasph::common::types::Object &object) const {
    return false;
}

bool ClassDefinition::operator>(const rasph::common::types::Object &object) const {
    return false;
}

std::unique_ptr<rasph::common::types::Object>
ClassDefinition::accept(const rasph::common::types::visitors::AddVisitor &visitor) const {
    throw std::runtime_error("Invalid call");
}

std::unique_ptr<rasph::common::types::Object>
ClassDefinition::accept(const rasph::common::types::visitors::SubtractVisitor &visitor) const {
    throw std::runtime_error("Invalid call");
}

std::unique_ptr<rasph::common::types::Object>
ClassDefinition::accept(const rasph::common::types::visitors::MultiplyVisitor &visitor) const {
    throw std::runtime_error("Invalid call");
}

std::unique_ptr<rasph::common::types::Object>
ClassDefinition::accept(const rasph::common::types::visitors::DivideVisitor &visitor) const {
    throw std::runtime_error("Invalid call");
}

rasph::common::types::Object *ClassDefinition::copyImplementation() const {
    return new common::types::ClassObject(*this);
}

const std::vector<std::string> &ClassDefinition::getAttributes() const {
    return attributes_;
}

rasph::common::ast::nodes::MethodMemberNode *ClassDefinition::getMethod(const std::string &method) const {
    return methods_.at(method);
}
