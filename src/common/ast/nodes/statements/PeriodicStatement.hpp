//
// Created by Piotr Żelazko on 05.06.2018.
//

#ifndef RASPH_PERIODICSTATEMENT_HPP
#define RASPH_PERIODICSTATEMENT_HPP

#include <common/tokens/tokens.h>
#include <common/tokens/Token.h>
#include <interpreter/environment/WorkerThread.hpp>
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

            using namespace interpreter::environment;

            std::function<void()> func = [block = block_.get()]() {
                block->execute();
            };

            block_.release();

            switch (timeSpecifier_.getType()){
                case common::tokens::TokenType::MIN:
                    WorkerThread::getInstance().addJob(func, WorkerThread::Minutes(static_cast<int>(periodValue_.getDoubleValue())));
                    break;
                case common::tokens::TokenType::SEC:
                    WorkerThread::getInstance().addJob(func, WorkerThread::Seconds(static_cast<int>(periodValue_.getDoubleValue())));
                    break;
                case common::tokens::TokenType::MS:
                    WorkerThread::getInstance().addJob(func, WorkerThread::Milliseconds(static_cast<int>(periodValue_.getDoubleValue())));
                    break;
                default:
                    throw std::runtime_error("Invalid token");
            }

        }

    private:
        const common::tokens::Token periodValue_;
        const common::tokens::Token timeSpecifier_;
        std::unique_ptr<nodes::BlockNode> block_;
    };
}

#endif //RASPH_PERIODICSTATEMENT_HPP
