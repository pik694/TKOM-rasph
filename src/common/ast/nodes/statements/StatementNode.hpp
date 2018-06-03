//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_STATEMENTNODE_HPP
#define RASPH_STATEMENTNODE_HPP

#include <common/ast/ProgramNode.hpp>

namespace rasph::common::ast::nodes {
    class StatementNode : public ProgramNode{
        virtual void execute() = 0;
    };
}


#endif //RASPH_STATEMENTNODE_HPP
