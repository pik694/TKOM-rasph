//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_BLOCKNODE_HPP
#define RASPH_BLOCKNODE_HPP

#include <memory>
#include <list>
#include <common/ast/ProgramNode.hpp>
#include "StatementNode.hpp"

namespace rasph::common::ast::nodes {
    class BlockNode : public StatementNode {
    public:

        void addStatement(std::unique_ptr<nodes::StatementNode> statement) {
            statements_.push_back(std::move(statement));
        }

        const std::list<std::unique_ptr<nodes::StatementNode>> &getStatements() const {
            return statements_;
        }

        void execute() override {
            for (auto& statement : statements_) {
                statement->execute();
            }
        }

    private:
        std::list<std::unique_ptr<nodes::StatementNode>> statements_;
    };
}


#endif //RASPH_BLOCKNODE_HPP
