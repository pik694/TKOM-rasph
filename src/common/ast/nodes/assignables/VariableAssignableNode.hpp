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

        explicit VariableAssignableNode(const std::string &name) : name_(name) {}

        const std::string &getName() const {
            return name_;
        }

    private:
        const std::string& name_;
    };

}


#endif //RASPH_IDENTASSIGNABLENODE_HPP
