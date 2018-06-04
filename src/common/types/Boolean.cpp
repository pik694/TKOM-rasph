//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Boolean.hpp"

using namespace rasph::common::types;

Boolean::Boolean(bool value) : value_(value) {}

bool Boolean::getValue() const {
    return value_;
}

void Boolean::setValue(bool value_) {
    this->value_ = value_;
}

Boolean::operator bool() const {
    return value_;
}

bool Boolean::operator!() const {
    return !value_;
}

Boolean *Boolean::copyImplementation() const {
    return new Boolean(*this);
}

std::unique_ptr<Boolean> Boolean::clone() const {
    return std::unique_ptr<Boolean>(this->copyImplementation());

}

bool Boolean::operator<(const Object &object) const {
    auto aBoolean = dynamic_cast<Boolean const &>(object);

    return value_ < aBoolean.value_;
}

bool Boolean::operator>(const Object &object) const {
    auto aBoolean = dynamic_cast<Boolean const &>(object);

    return value_ > aBoolean.value_;
}

std::unique_ptr<Object>
Boolean::accept(const visitors::AddVisitor &visitor) const {
    return visitor.add(*this);
}

std::unique_ptr<Object>
Boolean::accept(const visitors::SubtractVisitor &visitor) const {
    return visitor.subtract(*this);
}

std::unique_ptr<Object>
Boolean::accept(const visitors::MultiplyVisitor &visitor) const {
    return visitor.multiply(*this);
}

std::unique_ptr<Object>
Boolean::accept(const visitors::DivideVisitor &visitor) const {
    return visitor.divide(*this);
}


