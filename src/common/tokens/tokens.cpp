//
// Created by Piotr Żelazko on 25.04.2018.
//

#include "tokens.h"
#include <string>

namespace rasph::common::tokens {

    const std::unordered_map<std::string, TokenType> KEYWORDS = {
            {"for",    TokenType::FOR},
            {"if",     TokenType::IF},
            {"else",   TokenType::ELSE},
            {"in",     TokenType::IN},
            {"class",  TokenType::CLASS},
            {"func",   TokenType::FUNC},
            {"var",    TokenType::VAR},
            {"return", TokenType::RETURN},
            {"event",  TokenType::EVENT},
            {"handle", TokenType::HANDLE},
            {"with",   TokenType::WITH},
            {"m",      TokenType::M},
            {"w",      TokenType::W},
            {"d",      TokenType::D},
            {"h",      TokenType::H},
            {"min",    TokenType::MIN},
            {"sec",    TokenType::SEC},
            {"ms",     TokenType::MS},
            {"true",   TokenType::TRUE},
            {"false",  TokenType::FALSE},
            {"on",     TokenType::TRUE},
            {"off",    TokenType::FALSE},
            {"and",    TokenType::AND},
            {"or",     TokenType::OR}

    };


    const std::unordered_map<std::string, TokenType> SIMPLE_SIGNS{
            {"->", TokenType::ARROW},
            {"{",  TokenType::CBRACKET_LEFT},
            {"}",  TokenType::CBRACKET_RIGHT},
            {"(",  TokenType::PARENTHESIS_LEFT},
            {")",  TokenType::PARENTHESIS_RIGHT},
            {".",  TokenType::DOT},
            {",",  TokenType::COMMA},
            {"*",  TokenType::MULTIPLY},
            {"/",  TokenType::DIVIDE},
            {"+",  TokenType::PLUS},
            {"-",  TokenType::MINUS},
            {"=",  TokenType::ASSIGN},
            {"==", TokenType::EQUAL},
            {"!=", TokenType::NEQUAL},
            {"<",  TokenType::LESS},
            {"<=", TokenType::LEQUAL},
            {">",  TokenType::GREATER},
            {">=", TokenType::GEQUAL},
            {"!", TokenType::NOT}
    };

}