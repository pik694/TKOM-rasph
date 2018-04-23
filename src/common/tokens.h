//
// Created by Piotr Żelazko on 17.04.2018.
//

#ifndef RASPH_TOKEN_H
#define RASPH_TOKEN_H

#include <boost/spirit/include/lex_lexertl.hpp>


namespace rasph::common::tokens {

    namespace lex = boost::spirit::lex;

    using input_iterator_type =  std::istream_iterator<char>;


    using token_type =
    lex::lexertl::token<
            input_iterator_type,
            boost::mpl::vector<std::string>
    >;

    /// TOKENS' DECLARATIONS

    // Keywords

    extern lex::token_def<>
            if_token,
            else_token;
}


#endif //RASPH_TOKEN_H
