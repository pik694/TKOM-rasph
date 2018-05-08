//
// Created by Piotr Żelazko on 06.05.2018.
//

#include "common/ast/nodes/class_definition/ClassNode.hpp"
#include "common/ast/nodes/class_definition/members/MethodMemberNode.hpp"
#include "common/ast/nodes/class_definition/members/EventMemberNode.hpp"
#include "common/ast/nodes/class_definition/members/AttributeMemberNode.hpp"

#include "NodesFactory.hpp"

using namespace rasph::common::ast;
using namespace rasph::common::tokens;
using namespace rasph::common::ast::nodes;
using namespace rasph::parser;


/// PARSING METHODS

template<typename ... Args>
rasph::parser::node_ptr_t rasph::parser::Parser::tryParse() {
    return NodesFactory<Args...>(*this)();
}

template<>
rasph::parser::node_ptr_t rasph::parser::Parser::tryParse<>() {
    return nullptr;
}


template<>
rasph::parser::node_ptr_t rasph::parser::Parser::tryParse<nodes::ClassNode>() {
    // class
    auto tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CLASS) {
        unpeekTokens();
        return nullptr;
    }

    // identifier
    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::IDENTIFIER) {
        throw std::invalid_argument("Could not find class identifier");
    }

    auto classNode = new nodes::ClassNode(tmpToken->getTextValue());

    // {

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CBRACKET_LEFT) {
        throw std::invalid_argument("Could not find \"{\" ");
    }

    // members
    node_ptr_t node;
    while ((node = tryParse<nodes::EventMemberNode, nodes::AttributeMemberNode, nodes::MethodMemberNode>())) {

        auto member = std::unique_ptr<nodes::ClassMemberNode>(dynamic_cast<nodes::ClassMemberNode *>(node.get()));
        if (!member) throw std::bad_cast();
        node.release();

        classNode->addNode(std::move(member));

    }


    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CBRACKET_RIGHT) {
        throw std::invalid_argument("Could not find \"}\" ");
    }

    popTokens(4);
    return std::unique_ptr<ProgramNode>(classNode);

}


template<>
node_ptr_t Parser::tryParse<nodes::EventMemberNode>() {

    auto tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::EVENT) {
        unpeekTokens();
        return nullptr;
    }

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::IDENTIFIER)
        throw std::invalid_argument("Could not find event's identifier");

    popTokens(2);

    return std::unique_ptr<ProgramNode>(new nodes::EventMemberNode(tmpToken->getTextValue()));

}

template<>
node_ptr_t Parser::tryParse<nodes::AttributeMemberNode>() {
            auto tmpToken = peekToken();
        if(tmpToken->getType() != TokenType::VAR){
            unpeekTokens();
            return nullptr;
        }

        tmpToken = peekToken();
        if (tmpToken->getType() != TokenType::IDENTIFIER)
            throw std::invalid_argument("Could not find variable's identifier");

        popTokens(2);

        return std::unique_ptr<ProgramNode>(new nodes::AttributeMemberNode(tmpToken->getTextValue()));

}

template <>
node_ptr_t Parser::tryParse<nodes::MethodMemberNode>(){
    auto tmpToken = peekToken();
        if(tmpToken->getType() != TokenType::FUNC){
            unpeekTokens();
            return nullptr;
        }

        tmpToken = peekToken();
        if (tmpToken->getType() != TokenType::IDENTIFIER)
            throw std::invalid_argument("Could not find functions's identifier");

        auto method = new nodes::MethodMemberNode(tmpToken->getTextValue());

        tmpToken = peekToken();
        if (tmpToken->getType() != TokenType::PARENTHESIS_LEFT)
            throw std::invalid_argument("Could not find list of parameters");

        //TODO : list of parameters

        tmpToken = peekToken();
        if(tmpToken->getType() != TokenType::PARENTHESIS_RIGHT)
            throw std::invalid_argument("Could not find list of parameters");


        tmpToken = peekToken();
        if (tmpToken->getType() != TokenType::CBRACKET_LEFT)
            throw std::invalid_argument("Could not find method body");

        //TODO : statements

        tmpToken = peekToken();
        if (tmpToken->getType() != TokenType::CBRACKET_RIGHT)
            throw std::invalid_argument("Could not find method body");

        popTokens(6);

        return std::unique_ptr<ProgramNode>(method);
}

//node_ptr_t Parser::tryParse<nodes::MethodDefParametersList>() {
//
//}


/// OTHER MEMBERS
rasph::parser::Parser::Parser(std::unique_ptr<rasph::lexer::Lexer> lexer) : lexer_(std::move(lexer)) {}

std::shared_ptr<rasph::common::ast::ProgramTree> rasph::parser::Parser::parse() {

    auto programTree = std::make_shared<ProgramTree>();

    node_ptr_t node;

//    while ((node = (NodesFactory<ClassNode>(*this))())) {
    while ((node = tryParse<ClassNode>()))
        programTree->add(std::move(node));


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

    for (int i = 0; i < count; ++i) {
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












