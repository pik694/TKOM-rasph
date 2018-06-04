//
// Created by Piotr Żelazko on 04.06.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <lexer/Lexer.h>
#include <interpreter/Interpreter.hpp>
#include <parser/Parser.hpp>
#include <interpreter/environment/SymbolManager.hpp>
#include <common/types/Double.hpp>


using namespace rasph::common::types;
using namespace rasph::interpreter;
using namespace rasph::interpreter::environment;
using namespace rasph::lexer;
using namespace rasph::parser;

BOOST_AUTO_TEST_SUITE(interpreter_tests)


    BOOST_AUTO_TEST_CASE(empty_tree) {

        std::string sample_code = " ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), true);

        BOOST_REQUIRE_NO_THROW(tree->run());

    }

    BOOST_AUTO_TEST_CASE(simple_assignment_statement) {

        std::string sample_code = "a = 1";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();

        BOOST_REQUIRE_NO_THROW(SymbolManager::getInstance().getSymbol("a"));

        BOOST_REQUIRE_NO_THROW(auto a = dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()));

        BOOST_CHECK_EQUAL(dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 1.0);
    }

    BOOST_AUTO_TEST_CASE(simple_assignment_statements_with_value_change) {

        std::string sample_code = "a = 1\n a = 2";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 2.0);
    }

    BOOST_AUTO_TEST_CASE(assignment_with_simple_additon) {

        std::string sample_code = "a = 1 + 2";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 3.0);
    }




BOOST_AUTO_TEST_SUITE_END()
#endif

