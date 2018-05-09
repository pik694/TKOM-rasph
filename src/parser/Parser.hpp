//
// Created by Piotr Żelazko on 06.05.2018.
//

#ifndef RASPH_PARSER_HPP
#define RASPH_PARSER_HPP

#include <memory>
#include <deque>
#include <lexer/Lexer.h>
#include <common/ast/ProgramTree.hpp>
#include <common/ast/ProgramNode.hpp>
#include <stack>
#include <common/tokens/tokens.h>

namespace rasph::parser {

    using node_ptr_t = std::unique_ptr<rasph::common::ast::ProgramNode>;
    using token_ptr = std::shared_ptr<rasph::common::tokens::Token>;

    class Parser {
    public:
        Parser(std::unique_ptr<lexer::Lexer> lexer);

        Parser(const Parser &) = delete;

        std::shared_ptr<rasph::common::ast::ProgramTree> parse();

        virtual ~Parser() = default;

    private:

        template<typename ... Args>
        friend
        class NodesFactory;

        template<bool error, common::tokens::TokenType ... types>
        friend
        class TokenTypesAcceptor;

        template<typename T>
        std::unique_ptr<T> cast(node_ptr_t node){

            if(!node)
                throw std::invalid_argument("Expected not null");

            auto result = std::unique_ptr<T>(dynamic_cast<T*>(node.get()));
            node.release();
            return std::move(result);
        }

        std::shared_ptr<rasph::common::tokens::Token> peekToken();

        void unpeekTokens(size_t count = 1);

        void popTokens(size_t count = 1);

        template<typename ... Args>
        node_ptr_t tryParse();


        std::unique_ptr<rasph::lexer::Lexer> lexer_;
        std::deque<std::shared_ptr<rasph::common::tokens::Token>> tokensBuffer_;
        std::deque<std::shared_ptr<rasph::common::tokens::Token>> peekedTokens_;

    };
}

#endif //RASPH_PARSER_HPP
