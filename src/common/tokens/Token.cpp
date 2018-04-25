//
// Created by Piotr Żelazko on 24.04.2018.
//

#include <boost/optional.hpp>
#include "Token.h"

rasph::common::tokens::Token::Token(rasph::common::tokens::TokenType type) :
        type_(type) {
}

rasph::common::tokens::Token::Token(rasph::common::tokens::TokenType type, std::string value) :
        Token(type) {
    textValue_ = value;
}

rasph::common::tokens::Token::Token(rasph::common::tokens::TokenType type, double value) :
        Token(type) {
    doubleValue_ = value;
}


const rasph::common::tokens::TokenType rasph::common::tokens::Token::getType() const {
    return type_;
}

const std::string &rasph::common::tokens::Token::getTextValue() const {

    if (!textValue_.is_initialized())
        throw std::logic_error("String value is empty. Token type:"
                               + std::to_string(static_cast<uint8_t>(type_))
        );


    return textValue_.get();
}

const double &rasph::common::tokens::Token::getDoubleValue() const {

    if (!doubleValue_.is_initialized())
        throw std::logic_error("Double value is empty. Token type:"
                               + std::to_string(static_cast<uint8_t>(type_))
        );


    return doubleValue_.get();
}




