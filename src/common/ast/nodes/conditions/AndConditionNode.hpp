//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_ANDCONDITIONNODE_HPP
#define RASPH_ANDCONDITIONNODE_HPP


#include "EqualityConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class AndConditionNode : public AssignableNode {

    public:
        AndConditionNode(std::unique_ptr<EqualityConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(std::unique_ptr<EqualityConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        std::unique_ptr<types::Object> value() override {
            return std::unique_ptr<types::Object>(new types::Boolean(isTrue()));
        }

        bool isTrue() {
            for (auto &condition : conditions_) {

                bool a = condition->isEqual();
                if (!(condition->isEqual()))
                    return false;
            }
            return true;
        }

    private:
        std::list<std::unique_ptr<EqualityConditionNode>> conditions_;
    };
}


#endif //RASPH_ANDCONDITIONNODE_HPP
