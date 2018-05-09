//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_EXPRESSION_HPP
#define RASPH_EXPRESSION_HPP

#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include "MultiplicativeExpressionNode.hpp"

namespace rasph::common::ast::nodes {
    class ExpressionNode : public AssignableNode{
    public:

        explicit ExpressionNode(std::unique_ptr<MultiplicativeExpressionNode> expression){
            expressions_.push_back(std::move(expression));
        }

        void addExpression(rasph::common::tokens::TokenType token, std::unique_ptr<MultiplicativeExpressionNode> expression){
            if (token != TokenType::PLUS && token != TokenType::MINUS) throw std::invalid_argument("Expected additive operator (+/-)");

            expressions_.push_back(std::move(expression));
            operators_.push_back(token);

        }

    private:
        using TokenType = rasph::common::tokens::TokenType;
        std::list<std::unique_ptr<MultiplicativeExpressionNode>> expressions_;
        std::list<rasph::common::tokens::TokenType> operators_;


    };
}

#endif //RASPH_EXPRESSION_HPP
