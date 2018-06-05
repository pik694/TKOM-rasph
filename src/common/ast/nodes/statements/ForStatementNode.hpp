//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_FORNODE_HPP
#define RASPH_FORNODE_HPP

#include <string>

#include "BlockNode.hpp"
#include "../assignables/AssignableNode.hpp"
#include <common/types/Double.hpp>

using namespace rasph::common::types;

namespace rasph::common::ast::nodes {
    class ForStatementNode : public StatementNode {
    public:
        ForStatementNode(const std::string &iterator,
                         std::unique_ptr<nodes::AssignableNode> range,
                         std::unique_ptr<BlockNode> block) :
                iterator_(iterator),
                range_(std::move(range)),
                block_(std::move(block)) {}


        void execute() override {


            auto list = range_->value()->toList();

            for (auto value : list){
                interpreter::environment::SymbolManager::getInstance()
                        .saveSymbol(interpreter::environment::symbols::Symbol(iterator_, value->clone()));
                block_->execute();
            }
        }

    private:

        const std::string iterator_;
        const std::unique_ptr<nodes::AssignableNode> range_;
        const std::unique_ptr<nodes::BlockNode> block_;
    };
}


#endif //RASPH_FORNODE_HPP
