//
// Created by Piotr Żelazko on 06.05.2018.
//

#include <common/program/nodes/ClassNode.hpp>
#include "Parser.hpp"
#include "NodesFactory.hpp"

using namespace rasph::common::program;
using namespace rasph::common::tokens;
using namespace rasph::parser;

rasph::parser::Parser::Parser(std::unique_ptr<rasph::lexer::Lexer> lexer) : lexer_(std::move(lexer)) {}

std::shared_ptr<rasph::common::program::ProgramTree> rasph::parser::Parser::parse() {

    auto programTree = std::make_shared<ProgramTree>();

    node_ptr_t node;

    while ((node = (NodesFactory<traits::class_definition>(*this))())) {
        programTree->add(std::move(node));
    }

    return programTree;

}
