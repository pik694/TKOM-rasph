//
// Created by Piotr Żelazko on 24.04.2018.
//

#ifndef RASPH_TOKENS_H
#define RASPH_TOKENS_H


#include <cstdint>
#include <unordered_map>

namespace rasph::common::tokens {


    enum class TokenType : uint8_t {

        FOR,
        IF,
        ELSE,
        IN,
        CLASS,
        FUNC,
        VAR,
        RETURN,
        EVERY,
        EVENT,
        HANDLE,
        WITH,
        M, W, D, H, MIN, SEC, MS,
        TRUE, FALSE,

        ARROW,

        CBRACKET_LEFT,
        CBRACKET_RIGHT,
        PARENTHESIS_LEFT,
        PARENTHESIS_RIGHT,

        DOT, COMMA,
        MULTIPLY, DIVIDE,
        PLUS, MINUS, ASSIGN,

        EQUAL, NEQUAL,
        LESS, LEQUAL,
        GREATER, GEQUAL,

        AND, OR, NOT,

        NUM_LITERAL,
        TEXT_LITERAL,
        IDENTIFIER,
        END
    };

    extern const std::unordered_map<std::string, TokenType>
            SIMPLE_SIGNS,
            KEYWORDS;

}

#endif //RASPH_TOKENS_H
