//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_CONDITIONNODE_HPP
#define RASPH_CONDITIONNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include <common/types/Boolean.hpp>
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

        std::unique_ptr<types::Object> value() override {
            return std::unique_ptr<types::Object>(new types::Boolean(isTrue()));
        }

        operator bool(){
            return isTrue();
        }
        
        bool isTrue(){
            for (auto condition : conditions_){
                if (!static_cast<bool>(*condition->value()))
                    return false;
            }
            return true;
        }

    private:
        std::list<std::unique_ptr<AndConditionNode>> conditions_;
    };
}


#endif //RASPH_CONDITIONNODE_HPP
