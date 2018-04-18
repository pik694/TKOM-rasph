//
// Created by Piotr Żelazko on 17.04.2018.
//

#ifndef RASPH_TOKEN_H
#define RASPH_TOKEN_H

#include <boost/spirit/include/lex_lexertl.hpp>

namespace rasph::common::tokens {

    namespace lex = boost::spirit::lex;

    using token_type =
    lex::lexertl::token<
            std::string::iterator,
            boost::mpl::vector<std::string>
    >;

    /// TOKENS DEFINITIONS

    // Keywords

    lex::token_def<>
            if_token("if"),
            else_token("else"),
            for_token("for"),
            foreach_token("foreach");

    // Operators
    lex::token_def<>
            plus_token('+'),
            minus_token('-');

    // Others

    lex::token_def<std::string> identifier_token ("[a-zA-Z_][a-zA-Z0-9_]*");
    lex::token_def<double> const_double_token ("[1-9][0-9]*.[0-9]*[1-9]");
    lex::token_def<int> const_int_token ("[1-9][0-9]*");
}

#endif //RASPH_TOKEN_H
