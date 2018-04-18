//
// Created by Piotr Żelazko on 17.04.2018.
//

#include "Lexer.h"
#include "common/tokens.h"

using namespace rasph;
namespace token = common::tokens;
using namespace rasph::lexer;


Lexer::Lexer() {

    this->self = token::minus_token;
    this->self += token::if_token | token::else_token;

    this->self += token::const_int_token;
}
