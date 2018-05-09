//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_EQUALITYCONDITION_HPP
#define RASPH_EQUALITYCONDITION_HPP

#include "common/tokens/tokens.h"
#include "RelationalConditionNode.hpp"

namespace rasph::common::ast::nodes {

    class EqualityConditionNode : public ProgramNode {
    public:

        EqualityConditionNode(std::unique_ptr<RelationalConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(rasph::common::tokens::TokenType tokenType, std::unique_ptr<RelationalConditionNode> condition) {
            if (conditions_.size() != 1) throw std::runtime_error("Already ");\
            tokenType = tokenType;
            conditions_.push_back(std::move(condition));
        }

    private:
        std::list<std::unique_ptr<RelationalConditionNode>> conditions_;
        common::tokens::TokenType tokenType_;

    };
}

#endif //RASPH_EQUALITYCONDITION_HPP
