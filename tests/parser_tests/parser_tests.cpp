//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <lexer/Lexer.h>
#include <parser/Parser.hpp>
#include <common/ast/nodes/class_definition/ClassNode.hpp>
#include <common/ast/nodes/statements/StatementNode.hpp>
#include <common/ast/nodes/statements/BlockNode.hpp>

using namespace rasph::lexer;
using namespace rasph::common::tokens;
using namespace rasph::common::ast;
using namespace rasph::parser;

BOOST_AUTO_TEST_SUITE(parser_tests)


    BOOST_AUTO_TEST_CASE(parse_variable) {
        std::string sample_code = "1123";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        std::shared_ptr<ProgramTree> tree;

        BOOST_CHECK_NO_THROW(tree = parser.parse());
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

        std::string sample_code = "class aClass { func aFunc (a,b,c){} \n var aVar \n event anEvent }";

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
        BOOST_CHECK_NO_THROW(dynamic_cast<nodes::BlockNode *>(tree->getNodes().at(0).get()));


    }

    BOOST_AUTO_TEST_CASE(parse_nested_empty_block) {

        std::string sample_code = "{ { } }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();
        auto node = dynamic_cast<nodes::BlockNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getStatements().size(), 1);


    }




BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK