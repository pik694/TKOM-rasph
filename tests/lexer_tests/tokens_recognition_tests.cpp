//
// Created by Piotr Żelazko on 25.04.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <common/tokens/tokens.h>
#include "lexer/Lexer.h"

using namespace rasph::lexer;
using namespace rasph::common::tokens;


BOOST_AUTO_TEST_SUITE(lexer_unit_tests)


    BOOST_AUTO_TEST_CASE(check_simple_keywords_recognition) {

        std::for_each(KEYWORDS.begin(), KEYWORDS.end(), [](auto pair) {

            Lexer lexer(std::make_unique<std::stringstream>(pair.first));

            BOOST_CHECK(lexer.getNextToken().value().getType() == pair.second);

        });


    }

    BOOST_AUTO_TEST_CASE(check_simple_tokens_recognition) {

        std::for_each(SIMPLE_SIGNS.begin(), SIMPLE_SIGNS.end(), [](auto pair) {

            Lexer lexer(std::make_unique<std::stringstream>(pair.first));

            BOOST_CHECK(lexer.getNextToken().value().getType() == pair.second);

        });

    }


    BOOST_AUTO_TEST_CASE(check_tokens_recognition) {

        std::for_each(SIMPLE_SIGNS.begin(), SIMPLE_SIGNS.end(), [](auto pair) {

            Lexer lexer(std::make_unique<std::stringstream>("//comment \n //\"hello\"   \n     " + pair.first + " some other okens"));

            BOOST_CHECK(lexer.getNextToken().value().getType() == pair.second);

        });

    }


BOOST_AUTO_TEST_SUITE_END()

#endif //BOOST_TEST_DYN_LINK