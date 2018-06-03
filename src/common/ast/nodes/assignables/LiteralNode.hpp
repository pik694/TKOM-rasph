//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_LITERALNODE_HPP
#define RASPH_LITERALNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include <common/tokens/Token.h>
#include <common/types/Double.hpp>
#include <common/types/String.hpp>

namespace rasph::common::ast::nodes {
    class LiteralNode : public AssignableNode {
    public:
        LiteralNode(const tokens::Token &token_) : token_(token_) {}

        std::unique_ptr<types::Object> value() override {
            switch (token_.getType()) {
                case tokens::TokenType::NUM_LITERAL:
                    return std::unique_ptr<types::Object>(
                            new types::Double(token_.getDoubleValue())
                    );
                case tokens::TokenType::TEXT_LITERAL:
                    return std::unique_ptr<types::Object>(
                            new types::String(token_.getTextValue())
                    );
                default:
                    throw std::runtime_error("Invalid token type");
            }
        }

    public:

        void execute() override {}

    private:
        tokens::Token token_;
    };
}


#endif //RASPH_LITERALNODE_HPP
