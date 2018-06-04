//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "String.hpp"

using namespace rasph::common::types;

String::String(const std::string &value) : value_(value) {}

const std::string &String::getValue() const {
    return value_;
}

void String::setValue(const std::string &value_) {
    String::value_ = value_;
}

String::operator bool() const {
    return value_.size() == 0;
}

bool String::operator!() const {
    return !bool();
}

String *String::copyImplementation() const {
    return new String(*this);
}

std::unique_ptr<String> String::clone() const {
    return std::unique_ptr<String>(this->copyImplementation());
}

bool String::operator<(Object const &object) const {
    auto &aString = dynamic_cast<String const &>(object);
    return value_ < aString.value_;
}

bool String::operator>(Object const &object) const {
    auto &aString = dynamic_cast<String const &>(object);
    return value_ > aString.value_;
}

std::unique_ptr<Object>
String::accept(const visitors::AddVisitor &visitor) const {
    return visitor.add(*this);
}

std::unique_ptr<Object>
String::accept(const visitors::SubtractVisitor &visitor) const {
    return visitor.subtract(*this);
}

std::unique_ptr<Object>
String::accept(const visitors::MultiplyVisitor &visitor) const {
    return visitor.multiply(*this);
}

std::unique_ptr<Object>
String::accept(const visitors::DivideVisitor &visitor) const {
    return visitor.divide(*this);
}
