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
#include <interpreter/environment/WorkerThread.hpp>

#include <common/types/Double.hpp>
#include <common/types/String.hpp>
#include <common/types/Boolean.hpp>

#include <thread>
#include <chrono>

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
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("true0").getValue()).getValue(),
                true);
        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("true1").getValue()).getValue(),
                true);


        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("false0").getValue()).getValue(),
                false);
        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("false1").getValue()).getValue(),
                false);

    }


    BOOST_AUTO_TEST_CASE(if_simple_test_0) {

        std::string sample_code = "if 1 == 1 { a = true } else {a = false} ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Boolean const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), true);

    }


    BOOST_AUTO_TEST_CASE(if_simple_test_2) {

        std::string sample_code = "if 1 < 1 { a = 3 } else {a = 4} ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 4);

    }

    BOOST_AUTO_TEST_CASE(if_simple_test_3) {

        std::string sample_code = "if 1 <= 1 { a = 3 } else {a = 4} ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 3);

    }

    BOOST_AUTO_TEST_CASE(if_simple_test_4) {

        std::string sample_code = "if 2 > 1 { a = 5 } else {a = 6} ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 5);

    }

    BOOST_AUTO_TEST_CASE(if_simple_test_5) {

        std::string sample_code = "if 0 >= 1 { a = 5 } else {a = 6} ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 6);

    }

    BOOST_AUTO_TEST_CASE(for_loop_test) {
        std::string sample_code = "for i in 1 { a = i }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        tree->run();

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 1);
    }

    BOOST_AUTO_TEST_CASE(class_declaration_test) {

        std::string sample_code = "class SampleClass {}";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_NO_THROW(tree->run());


    }

    BOOST_AUTO_TEST_CASE(class_with_attributes_and_events) {

        std::string sample_code = "class SampleClass0 { var a \n var b \n event an_event }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_NO_THROW(tree->run());

    }

    BOOST_AUTO_TEST_CASE(class_with_method) {


        std::string sample_code = "class SampleClass1 { var a \n func aFunc () { a = 10} }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_NO_THROW(tree->run());

    }


    BOOST_AUTO_TEST_CASE(every_statement) {
        using namespace std::chrono_literals;

        std::string sample_code = "a = 0 \n every 200 ms { a = a + 1}";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        BOOST_CHECK_NO_THROW(tree->run());

        std::this_thread::sleep_for(1s);

        BOOST_CHECK_GE(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 4);

        WorkerThread::getInstance().close();

    }



//    BOOST_AUTO_TEST_CASE(method_invocation) {
//
//        std::string sample_code = "class SampleClass2 { var a \n func aFunc () { a = 10 \n return a} } \n object = SampleClass2 \n result = object.aFunc() \n result1 = object.a";
//
//        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
//                std::make_unique<std::stringstream>(sample_code)
//        );
//
//        Parser parser(std::move(lexer));
//
//        auto tree = parser.parse();
//
//        BOOST_CHECK_NO_THROW(tree->run());
//
//        BOOST_CHECK_EQUAL(
//                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("result").getValue()).getValue(), 10);
//
//    }

BOOST_AUTO_TEST_SUITE_END()
#endif

