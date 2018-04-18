//
// Created by Piotr Żelazko on 17.04.2018.
//

#ifndef RASPH_LEXER_H
#define RASPH_LEXER_H

#include <boost/spirit/include/lex_lexertl.hpp>
#include "common/tokens.h"

namespace rasph::lexer {

    namespace lex = boost::spirit::lex;
    using namespace rasph::common::tokens;

    class Lexer : lex::lexer<lex::lexertl::lexer<token_type>> {
    public:

        Lexer();

    private:

    };
}

#endif //RASPH_LEXER_H
