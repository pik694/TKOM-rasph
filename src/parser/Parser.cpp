//
// Created by Piotr Żelazko on 06.05.2018.
//

#include "common/ast/nodes/class_definition/ClassNode.hpp"
#include "Parser.hpp"
#include "NodesFactory.hpp"

using namespace rasph::common::program;
using namespace rasph::common::tokens;
using namespace rasph::common::program::nodes;
using rasph::parser::Parser;

rasph::parser::Parser::Parser(std::unique_ptr<rasph::lexer::Lexer> lexer) : lexer_(std::move(lexer)) {}

std::shared_ptr<rasph::common::program::ProgramTree> rasph::parser::Parser::parse() {

    auto programTree = std::make_shared<ProgramTree>();

    node_ptr_t node;

    while ((node = (NodesFactory<ClassNode>(*this))())) {
        programTree->add(std::move(node));
    }

    return programTree;

}

void Parser::popTokens(size_t count) {

    for (int i = 0; i < count; ++i) {
        if (peekedTokens_.empty())
            break;

        peekedTokens_.pop_front();
    }
}

void Parser::unpeekTokens(size_t count) {

    for(int i = 0; i < count; ++i){
        if (peekedTokens_.empty())
            throw std::out_of_range("Peeked tokens buffer is empty");

        tokensBuffer_.push_front(peekedTokens_.front());
        peekedTokens_.pop_front();
    };

}

std::shared_ptr<rasph::common::tokens::Token> Parser::peekToken() {

    std::shared_ptr<rasph::common::tokens::Token> token;

    if (!tokensBuffer_.empty()) {
        token = tokensBuffer_.front();
        tokensBuffer_.pop_front();
    } else {
        token = std::move(lexer_->getNextToken());
    }


    if (!token) {
        throw std::invalid_argument("There are no more tokens");
    }

    peekedTokens_.push_front(token);
    return token;

}




