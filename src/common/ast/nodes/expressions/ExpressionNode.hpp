//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_EXPRESSION_HPP
#define RASPH_EXPRESSION_HPP

#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include <common/tokens/tokens.h>
#include <list>
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

        std::unique_ptr<types::Object> value() override {

            auto exprIt = expressions_.begin();
            auto operIt = operators_.begin();

            auto value = (*exprIt)->value();
            ++exprIt;

            for (; exprIt != expressions_.end(); ++exprIt, ++operIt){
                switch(*operIt){
                    case TokenType::PLUS:
                        value = std::move(*value + *((*exprIt)->value()));
                        break;
                    case TokenType::MINUS:
                        value = std::move(*value - *((*exprIt)->value()));
                        break;
                    default:
                        throw std::invalid_argument("Expected additive operator (+/-)");
                }
            }

            return value;
        }

    private:
        using TokenType = rasph::common::tokens::TokenType;
        std::list<std::unique_ptr<MultiplicativeExpressionNode>> expressions_;
        std::list<rasph::common::tokens::TokenType> operators_;


    };
}

#endif //RASPH_EXPRESSION_HPP
