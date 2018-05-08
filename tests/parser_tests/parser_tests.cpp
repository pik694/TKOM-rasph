//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <lexer/Lexer.h>
#include <parser/Parser.hpp>
#include <common/ast/nodes/class_definition/ClassNode.hpp>

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


    BOOST_AUTO_TEST_CASE(parse_class_with_method) {

        std::string sample_code = "class aClass { func aFunc (){} \n var aVar \n event anEvent }";

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(
                std::make_unique<std::stringstream>(sample_code)
        );

        Parser parser(std::move(lexer));

        auto tree = parser.parse();

        auto node = dynamic_cast<nodes::ClassNode *>(tree->getNodes().at(0).get());

        BOOST_CHECK_EQUAL(node->getMembers().size(), 3);

    }


BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK