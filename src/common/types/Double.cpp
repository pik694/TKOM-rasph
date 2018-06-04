//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "Double.hpp"
#include "String.hpp"

using namespace rasph::common::types;

Double::Double(double value): value_(value) {}

double Double::getValue() const {
    return value_;
}

void Double::setValue(double value_) {
    Double::value_ = value_;
}


Double::operator bool() const {
    return value_ != 0.0;
}

bool Double::operator!() const {
    return !bool();
}

Double *Double::copyImplementation() const {
    return new Double(*this);
}

std::unique_ptr<Double> Double::clone() const {
    return std::unique_ptr<Double>(this->copyImplementation());

}

bool Double::operator<(Object const &object) const {

    auto &aDouble = dynamic_cast<Double const &>(object);

    return value_ < aDouble.value_;

}

bool Double::operator>(Object const &object) const {

    auto &aDouble = dynamic_cast<Double const &>(object);
    return value_ > aDouble.value_;
}

std::unique_ptr<Object>
Double::operator+(const Object &object) const {
    return object.accept(static_cast<visitors::AddVisitor const&>(*this));
}

std::unique_ptr<Object>
Double::operator-(const Object &object) const {
    return object.accept(static_cast<visitors::SubtractVisitor const&>(*this));
}

std::unique_ptr<Object>
Double::operator*(const Object &object) const {
    return object.accept(static_cast<visitors::MultiplyVisitor const&>(*this));
}

std::unique_ptr<Object>
Double::operator/(const Object &object) const {
    return object.accept(static_cast<visitors::DivideVisitor const&>(*this));
}

std::unique_ptr<Object> Double::accept(visitors::AddVisitor const &visitor) const {
    return visitor.add(*this);
}

std::unique_ptr<Object> Double::accept(visitors::SubtractVisitor const &visitor) const {
    return visitor.subtract(*this);
}

std::unique_ptr<Object> Double::accept(visitors::MultiplyVisitor const &visitor) const {
    return visitor.multiply(*this);
}

std::unique_ptr<Object> Double::accept(visitors::DivideVisitor const &visitor) const {
    return visitor.divide(*this);
}

std::unique_ptr<Object> Double::add(String const &string) const {
    return std::unique_ptr<Object>(new String(string.getValue() + std::to_string(value_)));
}

std::unique_ptr<Object> Double::add(Double const &aDouble) const {
    return std::unique_ptr<Object>(new Double(value_ + aDouble.value_));
}

std::unique_ptr<Object> Double::subtract(Double const &aDouble) const {
    return std::unique_ptr<Object>(new Double(value_ - aDouble.value_));;
}

std::unique_ptr<Object> Double::multiply(Double const &aDouble) const {
    return std::unique_ptr<Object>(new Double(value_ * aDouble.value_));
}

std::unique_ptr<Object> Double::divide(Double const &aDouble) const {
    return std::unique_ptr<Object>(new Double(value_ / aDouble.value_));
}
