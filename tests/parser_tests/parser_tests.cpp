//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <lexer/Lexer.h>
#include <parser/Parser.hpp>
#include <common/ast/nodes.hpp>

using namespace rasph::lexer;
using namespace rasph::common::tokens;
using namespace rasph::common::ast;
using namespace rasph::parser;

BOOST_AUTO_TEST_SUITE(parser_tests)


    BOOST_AUTO_TEST_CASE(parse_variable) {
        std::string sample_code = " ";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        std::shared_ptr<ProgramTree> tree;

        BOOST_REQUIRE_NO_THROW(tree = parser.parse());
        BOOST_CHECK_EQUAL(tree->isEmpty(), true);

    }

    BOOST_AUTO_TEST_CASE(parse_class) {

        std::string sample_code = "class aClass { event anEvent }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        auto node = dynamic_cast<nodes::ClassNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getName(), "aClass");

    }

    BOOST_AUTO_TEST_CASE(parse_class_with_two_members) {

        std::string sample_code = "class aClass { event anEvent \n var aVar }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        auto node = dynamic_cast<nodes::ClassNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getMembers().size(), 2);

    }


    BOOST_AUTO_TEST_CASE(parse_class_with_empty_method) {

        std::string sample_code = "class aClass { func aFunc (){} \n var aVar \n event anEvent }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        auto node = dynamic_cast<nodes::ClassNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getMembers().size(), 3);

    }

    BOOST_AUTO_TEST_CASE(parse_class_with_method_with_parametrs) {

        std::string sample_code = "class aClass { func aFunc (a,b,c){ return a } \n var aVar \n event anEvent }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        auto node = dynamic_cast<nodes::ClassNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getMembers().size(), 3);

    }

    BOOST_AUTO_TEST_CASE(parse_class_with_method_with_duplicate_parametrs) {

        std::string sample_code = "class aClass { func aFunc (a,b,c,b){} \n var aVar \n event anEvent }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));


        BOOST_CHECK_THROW(parser.parse(), std::invalid_argument);

    }

    BOOST_AUTO_TEST_CASE(parse_empty_block) {

        std::string sample_code = "{ }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();
        void* ptr;
        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::BlockNode *>(tree->getNodes().at(0).get()));


    }

    BOOST_AUTO_TEST_CASE(parse_nested_empty_block) {

        std::string sample_code = "{ { for i in abc {} } }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();
        auto node = dynamic_cast<nodes::BlockNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getStatements().size(), 1);


    }

    BOOST_AUTO_TEST_CASE(parse_for_statement) {

        std::string sample_code = "for i in Range {}";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();
        nodes::ForStatementNode * ptr;
        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::ForStatementNode *>(tree->getNodes().at(0).get()));

    }

    BOOST_AUTO_TEST_CASE(parse_assign_statement) {

        std::string sample_code = "a = b";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();
        nodes::AssignStatementNode * ptr;

        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::AssignStatementNode *>(tree->getNodes().at(0).get()));

    }


    BOOST_AUTO_TEST_CASE(parse_simple_if_statement) {

        std::string sample_code = "if !(a == c or a != b) and a > b { a =  b }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        void * ptr;
        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::IfStatementNode *>(tree->getNodes().at(0).get()));

    }

    BOOST_AUTO_TEST_CASE(parse_simple_add_statement) {

        std::string sample_code = "a = b + c - ab";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        void * ptr;
        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::ExpressionNode *>(tree->getNodes().at(0).get()));

    }

    BOOST_AUTO_TEST_CASE(parse_assign_literal) {

        std::string sample_code = "a = 12";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        void * ptr;
        BOOST_CHECK_NO_THROW(ptr = dynamic_cast<nodes::StatementNode *>(tree->getNodes().at(0).get()));

    }



BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK