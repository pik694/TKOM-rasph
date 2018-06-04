//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_EQUALITYCONDITION_HPP
#define RASPH_EQUALITYCONDITION_HPP

#include "common/tokens/tokens.h"
#include "RelationalConditionNode.hpp"

namespace rasph::common::ast::nodes {

    class EqualityConditionNode : public AssignableNode {
    public:

        EqualityConditionNode(std::unique_ptr<RelationalConditionNode> condition): tokenType_(tokens::TokenType::EQUAL) {
            conditions_.push_back(std::move(condition));
        }

        void addCondition(rasph::common::tokens::TokenType tokenType, std::unique_ptr<RelationalConditionNode> condition) {

            if (conditions_.size() != 1) throw std::runtime_error("Already full node");

            this->tokenType_ = tokenType;
            conditions_.push_back(std::move(condition));

        }

        std::unique_ptr<types::Object> value() override {
            return std::unique_ptr<types::Object>(new types::Boolean(isEqual()));
        }

        bool isEqual(){

            bool equality;
            if (conditions_.size() == 1)
                equality = static_cast<bool>(*(conditions_.at(0)->value()));

            else equality = *(conditions_.at(0)->value()) == *(conditions_.at(1)->value());
            return (tokenType_ == tokens::TokenType::EQUAL) == equality;
        }

    private:
        std::vector<std::unique_ptr<RelationalConditionNode>> conditions_;
        common::tokens::TokenType tokenType_;

    };
}

#endif //RASPH_EQUALITYCONDITION_HPP
