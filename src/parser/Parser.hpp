//
// Created by Piotr Żelazko on 06.05.2018.
//

#ifndef RASPH_PARSER_HPP
#define RASPH_PARSER_HPP

#include <memory>
#include <deque>
#include <lexer/Lexer.h>
#include <common/program/ProgramTree.hpp>
#include <common/program/ProgramNode.hpp>
#include <stack>

namespace rasph::parser {

    using node_ptr_t = std::unique_ptr<rasph::common::program::ProgramNode>;

    class Parser {
    public:
        Parser(std::unique_ptr<lexer::Lexer> lexer);

        Parser(const Parser &) = delete;

        std::shared_ptr<rasph::common::program::ProgramTree> parse();

        virtual ~Parser() = default;

    private:

        template<typename T>
        friend
        class SpecialisedNodeFactory;

        std::shared_ptr<rasph::common::tokens::Token> peekToken();

        void unpeekTokens(size_t count = 1);

        void popTokens(size_t count = 1);

        std::unique_ptr<rasph::lexer::Lexer> lexer_;
        std::deque<std::shared_ptr<rasph::common::tokens::Token>> tokensBuffer_;
        std::deque<std::shared_ptr<rasph::common::tokens::Token>> peekedTokens_;

    };
}

#endif //RASPH_PARSER_HPP
