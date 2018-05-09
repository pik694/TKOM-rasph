//
// Created by Piotr Żelazko on 06.05.2018.
//

#include <common/ast/nodes.hpp>

#include "NodesFactory.hpp"
#include "TokenTypesAcceptor.hpp"



using namespace rasph::common::ast;
using namespace rasph::common::tokens;
using namespace rasph::parser;

template<TokenType ... types>
using Acceptor = TokenTypesAcceptor<false, types ...  >;

template<TokenType ... types>
using AcceptorErr = TokenTypesAcceptor<true, types ...  >;





/// Specializations' declarations
template<>
node_ptr_t Parser::tryParse<nodes::BlockNode>();

template <>
node_ptr_t Parser::tryParse<nodes::ForStatementNode>();

template <>
node_ptr_t Parser::tryParse<nodes::AssignableNode>();

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
node_ptr_t Parser::tryParse<nodes::StatementNode>() {
    return tryParse<nodes::BlockNode, nodes::ForStatementNode>();
}

template<>
node_ptr_t Parser::tryParse<nodes::BlockNode>() {

    auto tmpToken = Acceptor<TokenType::CBRACKET_LEFT>(*this)();
    if (!tmpToken) return nullptr;

    auto block = new nodes::BlockNode ();

    node_ptr_t node;
    while ((node = tryParse<nodes::StatementNode>())){
        auto statement = cast<nodes::StatementNode>(std::move(node));
        block->addStatement(std::move(statement));
    }

    AcceptorErr<TokenType::CBRACKET_RIGHT>(*this)();

    return node_ptr_t(block);
}

template <>
node_ptr_t Parser::tryParse<nodes::ForStatementNode>() {

    auto tmpToken = Acceptor<TokenType::FOR>(*this)();
    if(!tmpToken) return nullptr;

    tmpToken = AcceptorErr<TokenType::IDENTIFIER>(*this)();
    std::string iterator = tmpToken->getTextValue();

    AcceptorErr<TokenType::IN>(*this)();

    auto assignable = cast<nodes::AssignableNode>(tryParse<nodes::AssignableNode>());

    auto block = cast<nodes::BlockNode>(std::move(tryParse<nodes::BlockNode>()));

    return node_ptr_t(new nodes::ForStatementNode(iterator, std::move(assignable), std::move(block)));
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
    if (tmpToken->getType() != TokenType::VAR) {
        unpeekTokens();
        return nullptr;
    }

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::IDENTIFIER)
        throw std::invalid_argument("Could not find variable's identifier");

    popTokens(2);

    return std::unique_ptr<ProgramNode>(new nodes::AttributeMemberNode(tmpToken->getTextValue()));

}

template<>
node_ptr_t Parser::tryParse<nodes::MethodMemberNode>() {
    auto tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::FUNC) {
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

    tmpToken = peekToken();
    if (tmpToken->getType() == TokenType::IDENTIFIER) {
        while (true) {

            method->addParameter(tmpToken->getTextValue());
            popTokens();

            tmpToken = peekToken();
            if (tmpToken->getType() != TokenType::COMMA) {
                unpeekTokens();
                break;
            }
            popTokens();

            tmpToken = peekToken();
            if (tmpToken->getType() != TokenType::IDENTIFIER) {
                throw std::invalid_argument("Expected identifier");
            }
        }
    } else {
        unpeekTokens();
    }

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::PARENTHESIS_RIGHT)
        throw std::invalid_argument("Could not find list of parameters");


    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CBRACKET_LEFT)
        throw std::invalid_argument("Could not find method body");


    // method body
    node_ptr_t node;
    while ((node = tryParse<nodes::StatementNode>())){
        auto statement = std::unique_ptr<nodes::StatementNode>(dynamic_cast<nodes::StatementNode *>(node.get()));
        if (!statement) throw std::bad_cast();
        node.release();

        method->addStatement(std::move(statement));

    }

    tmpToken = peekToken();
    if(tmpToken->getType() == TokenType::RETURN){
        popTokens();
        //TODO assignable
    } else unpeekTokens();

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CBRACKET_RIGHT)
        throw std::invalid_argument("Could not find method body");

    popTokens(6);

    return std::unique_ptr<ProgramNode>(method);
}

template <>
node_ptr_t Parser::tryParse<nodes::IdentAssignableNode>(){

    auto token = Acceptor<TokenType::IDENTIFIER>(*this)();
    if (!token) return nullptr;

    return node_ptr_t(new nodes::IdentAssignableNode(token->getTextValue()));

}

template <>
node_ptr_t Parser::tryParse<nodes::AssignableNode>(){
    return tryParse<nodes::IdentAssignableNode>();
}


/// OTHER MEMBERS
rasph::parser::Parser::Parser(std::unique_ptr<rasph::lexer::Lexer> lexer) : lexer_(std::move(lexer)) {}

std::shared_ptr<rasph::common::ast::ProgramTree> rasph::parser::Parser::parse() {

    auto programTree = std::make_shared<ProgramTree>();

    node_ptr_t node;

    while ((node = tryParse<nodes::ClassNode, nodes::StatementNode>()))
        programTree->add(std::move(node));

    if (!peekedTokens_.empty() || tokensBuffer_.front()->getType() != TokenType::END)
        throw std::runtime_error("Invalid buffers state");

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












