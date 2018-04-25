//
// Created by Piotr Żelazko on 24.04.2018.
//

#ifndef RASPH_LEXER_H
#define RASPH_LEXER_H

#include <iterator>
#include <istream>
#include <boost/optional.hpp>
#include "common/tokens/Token.h"


namespace rasph::lexer {

    using iterator_t = std::istream_iterator<char>;

    class Lexer {
    public:

        explicit Lexer(std::istream &inputStream);

        size_t getCurrentLine() const;

        size_t getCurrentColumn() const;

        boost::optional<rasph::common::tokens::Token> getNextToken();

        virtual ~Lexer() = default;

    private:


        class iterator_wrapper {
        public:

            iterator_wrapper(Lexer &lexer, iterator_t &&iterator) : lexer_(lexer), it_(iterator) {
            }

            explicit iterator_wrapper(Lexer &lexer) : lexer_(lexer), it_() {
            }

            const iterator_t &operator*() {
                return it_;
            }

            iterator_wrapper &operator++() {

                ++it_;
                ++lexer_.column_;

                if (*it_ == '\n') {
                    ++lexer_.line_;
                    lexer_.column_ = 0;
                }
                return *this;
            }

        private:
            Lexer &lexer_;
            iterator_t it_;
        };

        size_t line_ = 1;
        size_t column_ = 1;

        iterator_wrapper iterator_;
        iterator_t end_;
        std::istream &inputStream_;


        void skipWhitespacesAndComments();



        friend class Lexer::iterator_wrapper;

        rasph::common::tokens::Token getToken();

        rasph::common::tokens::Token getTextLiteralToken();

        rasph::common::tokens::Token getAlphaNumToken();

        rasph::common::tokens::Token parseNumberLiteral();
    };


}

#endif //RASPH_LEXER_H
