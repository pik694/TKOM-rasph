//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_RELATIONALCONDITIONNODE_HPP
#define RASPH_RELATIONALCONDITIONNODE_HPP

#include "ConditionNode.hpp"
#include "PrimaryConditionNode.hpp"
#include "common/types/Boolean.hpp"

namespace rasph::common::ast::nodes {
    class RelationalConditionNode : public AssignableNode {

    public:
        RelationalConditionNode(std::unique_ptr<PrimaryConditionNode> condition) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(rasph::common::tokens::TokenType tokenType, std::unique_ptr<PrimaryConditionNode> condition) {
            if (conditions_.size() != 1) throw std::runtime_error("Already full node");\

            this->tokenType_ = tokenType;
            conditions_.push_back(std::move(condition));
        }

        std::unique_ptr<types::Object> value() override {

            bool result = true;


            switch (tokenType_) {
                case tokens::TokenType::LESS:
                    result =  (*conditions_.at(0)->value()) < (*conditions_.at(0)->value());
                    break;
                case tokens::TokenType::LEQUAL:
                    result =  (*conditions_.at(0)->value()) <= (*conditions_.at(0)->value());
                    break;
                case tokens::TokenType::GREATER:
                    result =  (*conditions_.at(0)->value()) > (*conditions_.at(0)->value());
                    break;
                case tokens::TokenType::GEQUAL:
                    result =  (*conditions_.at(0)->value()) >= (*conditions_.at(0)->value());
                    break;
                default:
                    throw std::runtime_error("Invalid token type");
            }

            return std::unique_ptr<types::Object>(new types::Boolean(result));
        }

    private:
        std::vector<std::unique_ptr<PrimaryConditionNode>> conditions_;
        common::tokens::TokenType tokenType_;
    };
}

#endif //RASPH_RELATIONALCONDITIONNODE_HPP
