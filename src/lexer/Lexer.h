
// Created by Piotr Żelazko on 23.04.2018.
//

#ifndef RASPH_LEXER_H
#define RASPH_LEXER_H

#include <istream>
#include <boost/spirit/include/lex_lexertl.hpp>

#include "../common/tokens.h"

namespace rasph::lexer {

    using namespace rasph;
    using namespace boost::spirit;


    using lexer_type = lex::lexertl::lexer<common::tokens::token_type>;

    class Lexer : lex::lexer<lexer_type>{
    public:

    //     explicit Lexer(std::istream& inputStream);
        
    //     common::tokens::token_type nextToken();

    //     std::string getText();

    //     int getLine() const;

    //     int getColumn() const;

    // private:

    //     common::tokens::input_iterator_type inputBegin_;
    //     common::tokens::input_iterator_type inputEnd_;

    //     lexer_type::iterator_type iter_;
    //     lexer_type::iterator_type end_;

    //     int line_ = 1;
    //     int column_ = 1;

    };


}

#endif //RASPH_LEXER_H
