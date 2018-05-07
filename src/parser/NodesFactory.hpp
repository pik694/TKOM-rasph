//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_NODESFACTORY_HPP
#define RASPH_NODESFACTORY_HPP

#include "Parser.hpp"
#include <common/ast/nodes/class_definition/ClassNode.hpp>
#include <common/ast/nodes/class_definition/members/EventMemberNode.hpp>
#include <common/ast/nodes/class_definition/members/AttributeMemberNode.hpp>


namespace rasph::parser {

    using common::tokens::TokenType;
    using namespace common::program;

    template<typename... Args>
    class NodesFactory {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()() {
            return nullptr;
        }

    private:
        Parser &parser_;
    };


    template<typename T>
    class SpecialisedNodeFactory {
    public:
        SpecialisedNodeFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()();

    private:
        Parser &parser_;
    };

    template<typename T, typename... Args>
    class NodesFactory<T, Args...> {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()() {
            auto result = SpecialisedNodeFactory<T>(parser_)();
            return result ? std::move(result) : NodesFactory<Args...>(parser_)();
        }

    private:
        Parser &parser_;
    };

    template<>
    node_ptr_t SpecialisedNodeFactory<nodes::ClassNode>::operator()() {


        // class
        auto tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::CLASS) {
            parser_.unpeekTokens();
            return nullptr;
        }

        // identifier
        tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::IDENTIFIER) {
            throw std::invalid_argument("Could not find class identifier");
        }

        auto classNode = new nodes::ClassNode(tmpToken->getTextValue());

        // {

        tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::CBRACKET_LEFT) {
            throw std::invalid_argument("Could not find \"{\" ");
        }

        // members
        node_ptr_t node;
        while ((node = NodesFactory<nodes::EventMemberNode, nodes::AttributeMemberNode>(parser_)())) {

            auto member = std::unique_ptr<nodes::ClassMemberNode>(dynamic_cast<nodes::ClassMemberNode *>(node.get()));
            if (!member) throw std::bad_cast();
            node.release();

            classNode->addNode(std::move(member));

        }


        // }
        tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::CBRACKET_RIGHT) {
            throw std::invalid_argument("Could not find \"}\" ");
        }

        parser_.popTokens(4);
        return std::unique_ptr<ProgramNode>(classNode);
    }


    template<>
    node_ptr_t SpecialisedNodeFactory<nodes::EventMemberNode>::operator()() {

        auto tmpToken = parser_.peekToken();
        if(tmpToken->getType() != TokenType::EVENT){
            parser_.unpeekTokens();
            return nullptr;
        }

        tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::IDENTIFIER)
            throw std::invalid_argument("Could not find event's identifier");

        parser_.popTokens(2);

        return std::unique_ptr<ProgramNode>(new nodes::EventMemberNode(tmpToken->getTextValue()));

    }

    template<>
    node_ptr_t SpecialisedNodeFactory<nodes::AttributeMemberNode>::operator()() {

        auto tmpToken = parser_.peekToken();
        if(tmpToken->getType() != TokenType::VAR){
            parser_.unpeekTokens();
            return nullptr;
        }

        tmpToken = parser_.peekToken();
        if (tmpToken->getType() != TokenType::IDENTIFIER)
            throw std::invalid_argument("Could not find variable's identifier");

        parser_.popTokens(2);

        return std::unique_ptr<ProgramNode>(new nodes::AttributeMemberNode(tmpToken->getTextValue()));

    }


}


#endif //RASPH_NODESFACTORY_HPP
