//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_CONDITIONNODE_HPP
#define RASPH_CONDITIONNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include "AndConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class ConditionNode : public AssignableNode {
    public:
        ConditionNode(std::unique_ptr<AndConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(std::unique_ptr<AndConditionNode> condition){
                conditions_.push_back(std::move(condition));
        }

    private:
        std::list<std::unique_ptr<AndConditionNode>> conditions_;
    };
}


#endif //RASPH_CONDITIONNODE_HPP
