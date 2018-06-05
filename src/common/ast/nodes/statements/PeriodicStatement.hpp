//
// Created by Piotr Żelazko on 05.06.2018.
//

#ifndef RASPH_PERIODICSTATEMENT_HPP
#define RASPH_PERIODICSTATEMENT_HPP

#include <common/tokens/tokens.h>
#include <common/tokens/Token.h>
#include "StatementNode.hpp"
#include "BlockNode.hpp"

namespace rasph::common::ast::nodes {
    class PeriodicStatement : public StatementNode {
    public:

        PeriodicStatement(const tokens::Token &periodValue_, const tokens::Token &timeSpecifier_,
                          std::unique_ptr<BlockNode> block_) : periodValue_(periodValue_),
                                                               timeSpecifier_(timeSpecifier_),
                                                               block_(std::move(block_)) {}

        void execute() override {
            block_->execute();
        }

    private:
        const common::tokens::Token periodValue_;
        const common::tokens::Token timeSpecifier_;
        const std::unique_ptr<nodes::BlockNode> block_;
    };
}

#endif //RASPH_PERIODICSTATEMENT_HPP
