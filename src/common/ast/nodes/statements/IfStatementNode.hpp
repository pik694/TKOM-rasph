//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_IFSTATEMENTNODE_HPP
#define RASPH_IFSTATEMENTNODE_HPP

#include <memory>
#include <common/ast/nodes/conditions/ConditionNode.hpp>
#include "StatementNode.hpp"
#include "BlockNode.hpp"

namespace rasph::common::ast::nodes {
    class IfStatementNode : public StatementNode {

    public:
        IfStatementNode(std::unique_ptr<BlockNode> ifBlock, std::unique_ptr<ConditionNode> condition, std::unique_ptr<BlockNode> elseBlock = nullptr) :
                ifBlock_(std::move(ifBlock)),
                condition_(std::move(condition)),
                elseBlock_(std::move(elseBlock)) {}

    private:
        std::unique_ptr<BlockNode> ifBlock_;
        std::unique_ptr<ConditionNode> condition_;
        std::unique_ptr<BlockNode> elseBlock_;
    };
}


#endif //RASPH_IFSTATEMENTNODE_HPP
