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
using Acceptor = TokenTypesAcceptor<false, types ...>;

template<TokenType ... types>
using AcceptorErr = TokenTypesAcceptor<true, types ...>;


/// Declatations of specializations
template<>
node_ptr_t Parser::tryParse<nodes::BlockNode>();

template<>
node_ptr_t Parser::tryParse<nodes::ForStatementNode>();

template<>
node_ptr_t Parser::tryParse<nodes::AssignableNode>();

template<>
node_ptr_t Parser::tryParse<nodes::AssignStatementNode>();

template<>
node_ptr_t Parser::tryParse<nodes::IfStatementNode>();

template<>
node_ptr_t Parser::tryParse<nodes::ConditionNode>();

template <>
node_ptr_t Parser::tryParse<nodes::ExpressionNode>();

template<>
node_ptr_t Parser::tryParse<nodes::LiteralNode>();

template<>
node_ptr_t Parser::tryParse<nodes::VariableAssignableNode>();

/// PARSING METHODS

template<typename ... Args>
rasph::parser::node_ptr_t rasph::parser::Parser::tryParse() {
    return NodesFactory<Args...>(*this)();
}
template<>
rasph::parser::node_ptr_t rasph::parser::Parser::tryParse<>() {
    return nullptr;
}

template <>
node_ptr_t Parser::tryParse<nodes::PrimaryExpressionNode>() {

    std::unique_ptr<nodes::AssignableNode> node;

    if (Acceptor<TokenType::PARENTHESIS_LEFT>(*this)()) {

        node = cast<nodes::AssignableNode>(tryParse<nodes::ExpressionNode>());

        AcceptorErr<TokenType::PARENTHESIS_RIGHT>(*this)();

    }
    else node = cast<nodes::AssignableNode>(tryParse<nodes::LiteralNode, nodes::VariableAssignableNode>());

    return node ? node_ptr_t(new nodes::PrimaryExpressionNode(std::move(node))) : nullptr;
}

template <>
node_ptr_t Parser::tryParse<nodes::MultiplicativeExpressionNode>() {
    auto node = tryParse < nodes::PrimaryExpressionNode > ();
    if (!node) return nullptr;

    auto expression = new nodes::MultiplicativeExpressionNode(cast<nodes::PrimaryExpressionNode>(std::move(node)));

    auto acceptor = Acceptor<TokenType::DIVIDE, TokenType::MULTIPLY>(*this);
    std::shared_ptr<Token> token;
    while ((token = acceptor())) {
        expression->addExpression(token->getType(), cast<nodes::PrimaryExpressionNode>(tryParse < nodes::PrimaryExpressionNode> ()));
    }

    return node_ptr_t(expression);
}

template <>
node_ptr_t Parser::tryParse<nodes::ExpressionNode>() {

    auto node = tryParse < nodes::MultiplicativeExpressionNode > ();
    if (!node) return nullptr;

    auto expression = new nodes::ExpressionNode(cast<nodes::MultiplicativeExpressionNode>(std::move(node)));

    auto acceptor = Acceptor<TokenType::PLUS, TokenType::MINUS>(*this);
    std::shared_ptr<Token> token;
    while ((token = acceptor())) {
        expression->addExpression(token->getType(), cast<nodes::MultiplicativeExpressionNode>(tryParse < nodes::MultiplicativeExpressionNode> ()));
    }

    return node_ptr_t(expression);
}

template<>
node_ptr_t Parser::tryParse<nodes::LiteralNode>() {
    auto token = Acceptor<TokenType::TEXT_LITERAL, TokenType::NUM_LITERAL, TokenType::FALSE, TokenType::TRUE>(*this)();
    if (!token) return nullptr;

    return node_ptr_t(new nodes::LiteralNode(*token));
}

template<>
node_ptr_t Parser::tryParse<nodes::StatementNode>()  {
    //TODO : method call

    return tryParse < nodes::BlockNode, nodes::ForStatementNode, nodes::IfStatementNode, nodes::AssignStatementNode >
                                                                                         ();
}

template<>
node_ptr_t Parser::tryParse<nodes::BlockNode>() {

    auto tmpToken = Acceptor<TokenType::CBRACKET_LEFT>(*this)();
    if (!tmpToken) return nullptr;

    auto block = new nodes::BlockNode();

    node_ptr_t node;
    while ((node = tryParse < nodes::StatementNode > ())) {
        auto statement = cast<nodes::StatementNode>(std::move(node));
        block->addStatement(std::move(statement));
    }

    AcceptorErr<TokenType::CBRACKET_RIGHT>(*this)();

    return node_ptr_t(block);
}

template<>
node_ptr_t Parser::tryParse<nodes::ForStatementNode>() {

    auto tmpToken = Acceptor<TokenType::FOR>(*this)();
    if (!tmpToken) return nullptr;

    tmpToken = AcceptorErr<TokenType::IDENTIFIER>(*this)();
    std::string iterator = tmpToken->getTextValue();

    AcceptorErr<TokenType::IN>(*this)();

    auto assignable = cast<nodes::AssignableNode>(tryParse < nodes::AssignableNode > ());

    auto block = cast<nodes::BlockNode>(std::move(tryParse < nodes::BlockNode > ()));

    return node_ptr_t(new nodes::ForStatementNode(iterator, std::move(assignable), std::move(block)));
}

template<>
node_ptr_t Parser::tryParse<nodes::AssignStatementNode>() {

    auto token = Acceptor<TokenType::IDENTIFIER>(*this)();
    if (!token) return nullptr;

    const std::string ident = token->getTextValue();

    AcceptorErr<TokenType::ASSIGN>(*this)();

    auto node = cast<nodes::AssignableNode>(tryParse < nodes::AssignableNode > ());

    return node_ptr_t(new nodes::AssignStatementNode(ident, std::move(node)));
}

template <>
node_ptr_t Parser::tryParse<nodes::PrimaryConditionNode>() {

    bool inverted = false;

    auto unary = Acceptor<TokenType::NOT>(*this)();
    if(unary) inverted = true;

    std::unique_ptr<nodes::AssignableNode> node;

    if(Acceptor<TokenType::PARENTHESIS_LEFT>(*this)()){

        node = cast<nodes::AssignableNode>(tryParse<nodes::ConditionNode>());
        AcceptorErr<TokenType::PARENTHESIS_RIGHT>(*this)();

    }
    else{
        node = cast<nodes::AssignableNode>(tryParse<nodes::AssignableNode>());
    }

    return node_ptr_t(new nodes::PrimaryConditionNode(inverted, std::move(node)));
}

template <>
node_ptr_t Parser::tryParse<nodes::RelationalConditionNode>(){
    auto node = tryParse<nodes::PrimaryConditionNode>();
    if (!node) return nullptr;

    auto condition = new nodes::RelationalConditionNode(cast<nodes::PrimaryConditionNode>(std::move(node)));

    auto token = Acceptor<TokenType::GEQUAL, TokenType::LEQUAL, TokenType::LESS, TokenType::GREATER>(*this)();
    if (token){
        condition->addCondition(token->getType(), cast<nodes::PrimaryConditionNode>(tryParse<nodes::PrimaryConditionNode>()));
    }

    return node_ptr_t(condition);
}

template <>
node_ptr_t Parser::tryParse<nodes::EqualityConditionNode>() {

    auto node = tryParse<nodes::RelationalConditionNode>();
    if (!node) return nullptr;

    auto condition = new nodes::EqualityConditionNode(cast<nodes::RelationalConditionNode>(std::move(node)));

    auto token = Acceptor<TokenType::EQUAL, TokenType::NEQUAL>(*this)();
    if (token){
        condition->addCondition(token->getType(), cast<nodes::RelationalConditionNode>(tryParse<nodes::RelationalConditionNode>()));
    }

    return node_ptr_t(condition);

}

template<>
node_ptr_t Parser::tryParse<nodes::AndConditionNode>() {

    auto node = tryParse<nodes::EqualityConditionNode>();
    if (!node) return nullptr;

    auto condition = new nodes::AndConditionNode(cast<nodes::EqualityConditionNode>(std::move(node)));

    auto acceptor = Acceptor<TokenType::AND>(*this);
    while (acceptor()){
        condition->addCondition(cast<nodes::EqualityConditionNode>(tryParse<nodes::EqualityConditionNode>()));
    }

    return node_ptr_t(condition);

}

template<>
node_ptr_t Parser::tryParse<nodes::ConditionNode>() {

    auto node = tryParse<nodes::AndConditionNode>();
    if (!node) return nullptr;

    auto condition = new nodes::ConditionNode(cast<nodes::AndConditionNode>(std::move(node)));

    auto acceptor = Acceptor<TokenType::OR>(*this);
    while (acceptor()){
        condition->addCondition(cast<nodes::AndConditionNode>(tryParse<nodes::AndConditionNode>()));
    }

    return node_ptr_t(condition);
}

template<>
node_ptr_t Parser::tryParse<nodes::IfStatementNode>() {

    if (!Acceptor<TokenType::IF>(*this)()) return nullptr;

    auto condition = cast<nodes::ConditionNode>(tryParse < nodes::ConditionNode > ());

    auto ifBlock = cast<nodes::BlockNode>(tryParse < nodes::BlockNode > ());

    if (!Acceptor<TokenType::ELSE>(*this)())
        return node_ptr_t(new nodes::IfStatementNode(std::move(ifBlock), std::move(condition)));

    auto elseBlock = cast<nodes::BlockNode>(tryParse < nodes::BlockNode > ());

    return node_ptr_t(new nodes::IfStatementNode(std::move(ifBlock), std::move(condition), std::move(elseBlock)));

}

template<>
node_ptr_t Parser::tryParse<nodes::ClassNode>() {
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
    while ((node = tryParse < nodes::EventMemberNode, nodes::AttributeMemberNode, nodes::MethodMemberNode > ())) {

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
    while ((node = tryParse < nodes::StatementNode > ())) {
        auto statement = std::unique_ptr<nodes::StatementNode>(dynamic_cast<nodes::StatementNode *>(node.get()));
        if (!statement) throw std::bad_cast();
        node.release();

        method->addStatement(std::move(statement));

    }

    tmpToken = peekToken();
    if (tmpToken->getType() == TokenType::RETURN) {
        popTokens();

        method->setReturnStatement(cast<nodes::AssignableNode>(tryParse<nodes::AssignableNode>()));

    } else unpeekTokens();

    tmpToken = peekToken();
    if (tmpToken->getType() != TokenType::CBRACKET_RIGHT)
        throw std::invalid_argument("Could not find method body");

    popTokens(6);

    return std::unique_ptr<ProgramNode>(method);
}

template<>
node_ptr_t Parser::tryParse<nodes::VariableAssignableNode>() {


    //TODO : object member
    auto token = Acceptor<TokenType::IDENTIFIER>(*this)();
    if (!token) return nullptr;

    return node_ptr_t(new nodes::VariableAssignableNode(token->getTextValue()));

}

template<>
node_ptr_t Parser::tryParse<nodes::AssignableNode>() {
    return tryParse < nodes::ExpressionNode> ();
}


/// OTHER MEMBERS
rasph::parser::Parser::Parser(std::unique_ptr<rasph::lexer::Lexer> lexer) : lexer_(std::move(lexer)) {}

std::shared_ptr<rasph::common::ast::ProgramTree> rasph::parser::Parser::parse() {

    auto programTree = std::make_shared<ProgramTree>();

    node_ptr_t node;

    while ((node = tryParse<nodes::ClassNode, nodes::StatementNode>()))
        programTree->add(std::move(node));

    auto item = peekedTokens_.size();
    auto size1 = tokensBuffer_.size();
    auto token = tokensBuffer_.front();

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