//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <lexer/Lexer.h>
#include <parser/Parser.hpp>

using namespace rasph::lexer;
using namespace rasph::common::tokens;
using namespace rasph::common::program;
using namespace rasph::parser;

BOOST_AUTO_TEST_SUITE(parser_tests)


    BOOST_AUTO_TEST_CASE(parse_variable) {
        std::string sample_code = "1123";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser (std::move(lexer));

        std::shared_ptr<ProgramTree> tree;

        BOOST_CHECK_NO_THROW(tree = parser.parse());
        BOOST_CHECK_EQUAL(tree->isEmpty(), true);

    }


BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK