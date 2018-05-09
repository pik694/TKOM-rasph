//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_ANDCONDITIONNODE_HPP
#define RASPH_ANDCONDITIONNODE_HPP


#include "EqualityConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class AndConditionNode : public ProgramNode {

    public:
        AndConditionNode(std::unique_ptr<EqualityConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(std::unique_ptr<EqualityConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

    private:
        std::list<std::unique_ptr<EqualityConditionNode>> conditions_;
    };
}


#endif //RASPH_ANDCONDITIONNODE_HPP
