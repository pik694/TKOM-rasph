//
// Created by Piotr Żelazko on 04.06.2018.
//

#include <memory>
#include "OperatorVisitor.hpp"

namespace rasph::common::types::visitors {


    std::unique_ptr<Object> AddVisitor::add(String const &) const {
        throw std::runtime_error("Cannot add a string");
    }

    std::unique_ptr<Object> AddVisitor::add(Boolean const &) const {
        throw std::runtime_error("Cannot add a boolean");
    }

    std::unique_ptr<Object> AddVisitor::add(ClassObject const &) const {
        throw std::runtime_error("Cannot add a class object");
    }

    std::unique_ptr<Object> AddVisitor::add(Double const &) const { throw std::runtime_error("Cannot add a double"); }

    AddVisitor::~AddVisitor() {}


    std::unique_ptr<Object> SubtractVisitor::subtract(String const &) const {
        throw std::runtime_error("Cannot subtract a string");
    }

    std::unique_ptr<Object> SubtractVisitor::subtract(Boolean const &) const {
        throw std::runtime_error("Cannot subtract a boolean");
    }

    std::unique_ptr<Object> SubtractVisitor::subtract(ClassObject const &) const {
        throw std::runtime_error("Cannot subtract a class object");
    }

    std::unique_ptr<Object> SubtractVisitor::subtract(Double const &) const {
        throw std::runtime_error("Cannot subtract a double");
    }

    SubtractVisitor::~SubtractVisitor() {}


    std::unique_ptr<Object> MultiplyVisitor::multiply(String const &) const {
        throw std::runtime_error("Cannot multiply a string");
    }

    std::unique_ptr<Object> MultiplyVisitor::multiply(Boolean const &) const {
        throw std::runtime_error("Cannot multiply a boolean");
    }

    std::unique_ptr<Object> MultiplyVisitor::multiply(ClassObject const &) const {
        throw std::runtime_error("Cannot multiply a class object");
    }

    std::unique_ptr<Object> MultiplyVisitor::multiply(Double const &) const {
        throw std::runtime_error("Cannot multiply a double");
    }

    MultiplyVisitor::~MultiplyVisitor() {}


    std::unique_ptr<Object> DivideVisitor::divide(String const &) const {
        throw std::runtime_error("Cannot divide a string");
    }

    std::unique_ptr<Object> DivideVisitor::divide(Boolean const &) const {
        throw std::runtime_error("Cannot divide a boolean");
    }

    std::unique_ptr<Object> DivideVisitor::divide(ClassObject const &) const {
        throw std::runtime_error("Cannot divide a class object");
    }

    std::unique_ptr<Object> DivideVisitor::divide(Double const &) const {
        throw std::runtime_error("Cannot divide a double");
    }

    DivideVisitor::~DivideVisitor() {}


}

