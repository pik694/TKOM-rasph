//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_IDENTASSIGNABLENODE_HPP
#define RASPH_IDENTASSIGNABLENODE_HPP


#include <string>
#include "AssignableNode.hpp"

namespace rasph::common::ast::nodes {

    class VariableAssignableNode : public AssignableNode {
    public:

        explicit VariableAssignableNode(std::string &&name) : name_(name) {}

        const std::string &getName() const {
            return name_;
        }

        std::unique_ptr<types::Object> value() override {
            //TODO: get value from SymbolManager
            throw std::runtime_error("TODO");
        }

    private:
        const std::string name_;
    };

}


#endif //RASPH_IDENTASSIGNABLENODE_HPP
