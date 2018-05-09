//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_PRIMARYCONDITIONNODE_HPP
#define RASPH_PRIMARYCONDITIONNODE_HPP


#include "ConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class PrimaryConditionNode : public ProgramNode {
    public:
        PrimaryConditionNode(const bool inverted_, std::unique_ptr<AssignableNode> node_) :
                inverted_(inverted_),
                node_(std::move(node_)) {}

    private:
        const bool inverted_;
        const std::unique_ptr<AssignableNode> node_;
    };
}

#endif //RASPH_PRIMARYCONDITIONNODE_HPP
