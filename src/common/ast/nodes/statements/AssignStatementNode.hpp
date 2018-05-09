//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_ASSIGNSTATEMENTNODE_HPP
#define RASPH_ASSIGNSTATEMENTNODE_HPP

#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include <common/ast/nodes/assignables/VariableAssignableNode.hpp>
#include "StatementNode.hpp"

namespace rasph::common::ast::nodes {
    class AssignStatementNode : public StatementNode {
    public:


        AssignStatementNode(const std::string &lValue_, std::unique_ptr<AssignableNode> rValue_) :
                lValue_(lValue_),
                rValue_(std::move(rValue_)) {}

    private:
        const std::string lValue_;
        std::unique_ptr<AssignableNode> rValue_;

    };
}


#endif //RASPH_ASSIGNSTATEMENTNODE_HPP
