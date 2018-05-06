//
// Created by Piotr Żelazko on 24.04.2018.
//


#include <ios>
#include "Lexer.h"

using namespace rasph::common::tokens;


size_t rasph::lexer::Lexer::getCurrentLine() const {
    return line_;
}

size_t rasph::lexer::Lexer::getCurrentColumn() const {
    return column_;
}

rasph::lexer::Lexer::Lexer(std::unique_ptr<std::istream> &&inputStream) :
        inputStream_(std::move(inputStream)),
        iterator_(*this, (*inputStream) >> std::noskipws), // do not skip whitespaces
        end_() {

}

boost::optional<Token> rasph::lexer::Lexer::getNextToken() {

    skipWhitespacesAndComments();

    const int tokenColumn = column_;
    const int tokenLine = line_;

    if (*iterator_ == end_) return boost::none;

    return getToken();

}

void rasph::lexer::Lexer::skipWhitespacesAndComments() {


    bool comment = false;

    while (*iterator_ != end_) {

        if (**iterator_ == '/' && inputStream_->peek() == '/') {
            comment = true;
        }
        if (**iterator_ == '\n') comment = false;

        if (comment || **iterator_ == ' ' || **iterator_ == '\n')
            ++iterator_;

        else break;
    }

}


Token rasph::lexer::Lexer::getToken() {


    if (std::isalnum(**iterator_) ||
        **iterator_ == '_') // Alphanumeric - it will number, literal, keyword or identifier

        return getAlphaNumToken();

    else if (**iterator_ == '\"')  // Text literal start

        return getTextLiteralToken();

    else {
        std::string simple(1, **iterator_);
        const auto endIt = common::tokens::SIMPLE_SIGNS.end();

        if (SIMPLE_SIGNS.find(simple) != endIt) {

            TokenType tokenType = SIMPLE_SIGNS.at(simple);
            ++iterator_;

            if (*iterator_ != end_ && SIMPLE_SIGNS.find(simple + (**iterator_)) != endIt) {
                tokenType = SIMPLE_SIGNS.at(simple + (**iterator_));
                ++iterator_;
            }

            return Token(tokenType);

        }
    }

    throw std::invalid_argument("Could not tokenize. "
                                "Line: " + std::to_string(line_) +
                                " Column: " + std::to_string(column_));

}

Token rasph::lexer::Lexer::getTextLiteralToken() {

    std::string textLiteral;
    ++iterator_;

    while (*iterator_ != end_ && **iterator_ != '\"') {
        textLiteral += **iterator_;
        ++iterator_;
    }

    if (*iterator_ == end_)
        throw std::invalid_argument("Could not tokenize. "
                                    "Line: " + std::to_string(line_) +
                                    " Column: " + std::to_string(column_));


    ++iterator_;

    return Token(TokenType::TEXT_LITERAL, textLiteral);
}

Token rasph::lexer::Lexer::getAlphaNumToken() {

    if (std::isdigit(**iterator_)) {
        return parseNumberLiteral();
    }

    std::string ident;

    while (*iterator_ != end_ && (std::isalnum(**iterator_) || **iterator_ == '_')) {
        ident += **iterator_;
        ++iterator_;
    }

    if (KEYWORDS.find(ident) != KEYWORDS.end())
        return Token(KEYWORDS.at(ident));

    return Token(TokenType::IDENTIFIER, ident);


}

Token rasph::lexer::Lexer::parseNumberLiteral() {

    std::string number;
    bool wasComma = false;


    while (*iterator_ != end_ && (std::isdigit(**iterator_) || **iterator_ == '.')) {

        if (**iterator_ == '.') {
            if (!wasComma) {
                wasComma = true;
            } else {
                throw std::invalid_argument("Could not tokenize. "
                                            "Line: " + std::to_string(line_) +
                                            " Column: " + std::to_string(column_));
            }
        }
        number += **iterator_;
        ++iterator_;
    }

    double value;

    try {

        value = std::stod(number);

    } catch (const std::exception &e) {
        std::clog << e.what();
        throw std::invalid_argument("Could not tokenize. "
                                    "Line: " + std::to_string(line_) +
                                    " Column: " + std::to_string(column_));
    }

    return Token(TokenType::NUM_LITERAL, value);
}
