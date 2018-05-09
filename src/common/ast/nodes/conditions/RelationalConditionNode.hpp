//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_RELATIONALCONDITIONNODE_HPP
#define RASPH_RELATIONALCONDITIONNODE_HPP

#include "ConditionNode.hpp"
#include "PrimaryConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class RelationalConditionNode : public ProgramNode {

    public:
        RelationalConditionNode(std::unique_ptr<PrimaryConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(rasph::common::tokens::TokenType tokenType, std::unique_ptr<PrimaryConditionNode> condition) {
            if (conditions_.size() != 1) throw std::runtime_error("Already ");\
            tokenType = tokenType;
            conditions_.push_back(std::move(condition));
        }

    private:
        std::list<std::unique_ptr<PrimaryConditionNode>> conditions_;
        common::tokens::TokenType tokenType_;
    };
}

#endif //RASPH_RELATIONALCONDITIONNODE_HPP
