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
#include <common/types/String.hpp>
#include <common/types/Boolean.hpp>


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

        BOOST_REQUIRE_NO_THROW(
                auto a = dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()));

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 1.0);
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


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 2.0);
    }

    BOOST_AUTO_TEST_CASE(assignment_with_doubles_additon) {

        std::string sample_code = "a = 1 + 2";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 3.0);
    }

    BOOST_AUTO_TEST_CASE(assignment_with_doubles_subtraction) {

        std::string sample_code = "a = 1 - 2";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), -1);
    }


    BOOST_AUTO_TEST_CASE(assignment_with_doubles_multiplication) {

        std::string sample_code = "a = 2 * 2.5";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 5);
    }


    BOOST_AUTO_TEST_CASE(assignment_with_doubles_division) {

        std::string sample_code = "a = 1 / 2";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 0.5);
    }

    BOOST_AUTO_TEST_CASE(double_string_additon) {

        std::string sample_code = "a = 1 + \" test\"";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<String const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(),
                std::string("1.000000 test"));
    }

    BOOST_AUTO_TEST_CASE(invalid_double_operators) {

        std::string sample_code = "a = 1 + true";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        BOOST_CHECK_THROW(tree->run(), std::runtime_error);


    }

    BOOST_AUTO_TEST_CASE(assignment_and_update) {

        std::string sample_code = "a = 1 \n a = 1 + a";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 2);


    }

    BOOST_AUTO_TEST_CASE(assignment_with_identifiers_only_addition) {

        std::string sample_code = "a = 1 \n a = a + a";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 2);

    }

    BOOST_AUTO_TEST_CASE(assignment_with_identifiers_only_multiplication) {

        std::string sample_code = "a = 2 \n a = a * a";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 4);

    }

    BOOST_AUTO_TEST_CASE(assignment_string_addition) {

        std::string sample_code = "a = \"1\" + \"2\"";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<String const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(),
                std::string("12"));
    }


    BOOST_AUTO_TEST_CASE(assignment_bool) {

        std::string sample_code = "true0 = true \n true1 = on \n false0 = false \n false1 = off";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("true0").getValue()).getValue(), true);
        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("true1").getValue()).getValue(), true);



        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("false0").getValue()).getValue(), false);
        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("false1").getValue()).getValue(), false);

    }


    BOOST_AUTO_TEST_CASE(assignment_bool_condition) {

        std::string sample_code = "true0 = 1 == 1";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_EQUAL(tree->isEmpty(), false);

        tree->run();


        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("true0").getValue()).getValue(), true);

    }


BOOST_AUTO_TEST_SUITE_END()
#endif

