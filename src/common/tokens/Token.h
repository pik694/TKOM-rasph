//
// Created by Piotr Żelazko on 24.04.2018.
//

#ifndef RASPH_TOKEN_H
#define RASPH_TOKEN_H

#include "tokens.h"
#include <iostream>
#include <boost/optional.hpp>

namespace rasph::common::tokens {


    class Token {

        using iterator_t = std::istream_iterator<char>;

    public:

        Token(TokenType type, std::string value);

        Token(TokenType type, double value);

        explicit Token(TokenType type);

        const TokenType getType() const;

        const std::string &getTextValue() const;

        const double &getDoubleValue() const;

        virtual ~Token() = default;

    private:
        const TokenType type_;
        boost::optional<std::string> textValue_;
        boost::optional<double> doubleValue_;

    };

}

#endif //RASPH_TOKEN_H
