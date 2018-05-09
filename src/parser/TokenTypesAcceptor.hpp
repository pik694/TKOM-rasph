//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_TOKENTYPESACCEPTOR_HPP
#define RASPH_TOKENTYPESACCEPTOR_HPP

#include <common/tokens/tokens.h>
#include <common/tokens/Token.h>
#include "Parser.hpp"

namespace rasph::parser{


    template<bool error, common::tokens::TokenType ... types>
    struct TokenTypesAcceptor {
        TokenTypesAcceptor(Parser &parser_) : parser_(parser_) {}

        std::shared_ptr<rasph::common::tokens::Token> operator()() {

        }

    private:
        Parser &parser_;
    };

    template<bool error, common::tokens::TokenType type, common::tokens::TokenType ... types>
    struct TokenTypesAcceptor<error, type, types...> {
        TokenTypesAcceptor(Parser &parser_) : parser_(parser_) {}

        std::shared_ptr<rasph::common::tokens::Token> operator()() {

            auto tmp = parser_.peekToken();
            if (tmp->getType() == type) {
                parser_.popTokens();
                return tmp;
            }
            parser_.unpeekTokens();

            return TokenTypesAcceptor<error, types ... >(parser_)();

        }

    private:
        Parser &parser_;
    };

    template <>
    token_ptr TokenTypesAcceptor<false>::operator()() {
        return nullptr;
    }

    template <>
    token_ptr TokenTypesAcceptor<true>::operator()(){
        throw std::invalid_argument("Did not expect this token");
    }


}

#endif //RASPH_TOKENTYPESACCEPTOR_HPP
