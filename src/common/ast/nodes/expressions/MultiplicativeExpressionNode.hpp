//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_MULTIPLICATIVEEXPRESSIONNODE_HPP
#define RASPH_MULTIPLICATIVEEXPRESSIONNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include "PrimaryExpressionNode.hpp"

namespace rasph::common::ast::nodes {
    class MultiplicativeExpressionNode : public  AssignableNode {
    public:


        explicit MultiplicativeExpressionNode(std::unique_ptr<PrimaryExpressionNode> expression){
            expressions_.push_back(std::move(expression));
        }

        void addExpression(rasph::common::tokens::TokenType token, std::unique_ptr<PrimaryExpressionNode> expression){

            if (token != TokenType::DIVIDE && token != TokenType::MULTIPLY) throw std::invalid_argument("Expected additive operator (* or /)");

            expressions_.push_back(std::move(expression));
            operators_.push_back(token);

        }

        std::unique_ptr<types::Object> value() override {
            return expressions_.front()->value();
        }

        void execute() override {
            //TODO
            throw std::runtime_error("Not implemented yet");
        }

    private:

        using TokenType = rasph::common::tokens::TokenType;

        std::list<std::unique_ptr<PrimaryExpressionNode>> expressions_;
        std::list<rasph::common::tokens::TokenType> operators_;
    };
}


#endif //RASPH_MULTIPLICATIVEEXPRESSIONNODE_HPP
