// //
// // Created by Piotr Żelazko on 23.04.2018.



// #include "Lexer.h"

// #include <boost/spirit/include/lex_char_token_def.hpp>

// using namespace rasph::lexer;
// using namespace rasph::common::tokens;

// int Lexer::getLine() const {
//     return line_;
// }

// int Lexer::getColumn() const {
//     return column_;
// }

// Lexer::Lexer(std::istream &inputStream) :
//         inputBegin_(inputStream >> std::noskipws), // do not skip whitespaces
//         inputEnd_() {


//     // Register tokens
//     this->self = if_token
//     this->self += any;


//     // Initialise iterators
//     iter_ = this->begin(inputBegin_, inputEnd_);
//     end_ = this->end();
// }


// common::tokens::token_type Lexer::nextToken() {


//     if (iter_ != end_)
//         if (token_is_valid(*iter_))
//             if (iter_->id() == any.id()) {
//                 ++iter_;
//                 return nextToken();
//             } else
//                 return *(iter_++);
//         else
//             throw std::invalid_argument(
//                     "Invalid token! Line : " + std::to_string(line_) + ", column : " + std::to_string(column_)
//             );
//     else
//         return *iter_;

//     //TODO : bahaves badly when text ends (no option to know imediately that it ended
//     // Boost.Optional ?

// }

// std::string Lexer::getText() {

//     std::string resultingString = "";

//     std::for_each(inputBegin_, inputEnd_, [&resultingString](const char &c) { resultingString += c; });

//     return resultingString;

// }
