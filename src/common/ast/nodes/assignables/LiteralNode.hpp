//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_LITERALNODE_HPP
#define RASPH_LITERALNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include <common/tokens/Token.h>

namespace rasph::common::ast::nodes {
    class LiteralNode : public AssignableNode {
    public:
        LiteralNode(const tokens::Token &token_) : token_(token_) {}

    private:
        tokens::Token token_;
    };
}


#endif //RASPH_LITERALNODE_HPP
