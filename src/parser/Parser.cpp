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

void Parser::popToken() {
    if (!peekedTokens_.empty()) {
        peekedTokens_.pop();
    }
}

void Parser::unpeekToken() {
    if (!peekedTokens_.empty()) {
        tokensBuffer_.push_front(peekedTokens_.top());
    }
}

std::shared_ptr<rasph::common::tokens::Token> Parser::peekToken() {

    std::shared_ptr<rasph::common::tokens::Token> token;

    if (!tokensBuffer_.empty()) {
        token = tokensBuffer_.front();
        tokensBuffer_.pop_front();
    }
    else{
        token = std::move(lexer_->getNextToken());
    }


    if (!token){
        throw std::invalid_argument("There are no more tokens");
    }

    peekedTokens_.push(token);
    return token;

}




