//
// Created by Piotr Żelazko on 24.04.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <common/tokens/tokens.h>
#include "lexer/Lexer.h"

using namespace rasph::lexer;
using namespace rasph::common::tokens;


BOOST_AUTO_TEST_SUITE(lexer_unit_tests)


    BOOST_AUTO_TEST_CASE(check_proper_initialization) {

        const std::string someTextString = " if else for while ident + 1 -1 80 in handle ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        BOOST_CHECK_EQUAL(lexer.getCurrentColumn(), 1);
        BOOST_CHECK_EQUAL(lexer.getCurrentLine(), 1);


    }

    BOOST_AUTO_TEST_CASE(return_first_valid_token) {

        const std::string someTextString = "12345\n123456789\n1\n";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        BOOST_CHECK(lexer.getNextToken().is_initialized());

    }

    BOOST_AUTO_TEST_CASE(recognise_first_valid_token) {

        const std::string someTextString = "12345\n123456789\n1\n";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);


        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);

    }


    BOOST_AUTO_TEST_CASE(should_skip_spaces_and_change_position) {

        const std::string someTextString = "  \n \n \n 123456789\n1\n";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);

        BOOST_CHECK_EQUAL(lexer.getCurrentColumn(), 0);
        BOOST_CHECK_EQUAL(lexer.getCurrentLine(), 5);

    }

    BOOST_AUTO_TEST_CASE(should_skip_comment_and_change_position) {

        const std::string someTextString = "// 123456789\n 1\n";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        lexer.getNextToken();

        BOOST_CHECK_EQUAL(lexer.getCurrentColumn(), 0);
        BOOST_CHECK_EQUAL(lexer.getCurrentLine(), 3);

    }

    BOOST_AUTO_TEST_CASE(chained_comments) {

        const std::string someTextString = "// 123456789\n // 1 \n  12";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        lexer.getNextToken();

        BOOST_CHECK_EQUAL(lexer.getCurrentColumn(), 5);
        BOOST_CHECK_EQUAL(lexer.getCurrentLine(), 3);

    }

    BOOST_AUTO_TEST_CASE(comment_inside_comment) {

        const std::string someTextString = "// 123456789// commenbt\n1 \n  12";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        lexer.getNextToken();

        BOOST_CHECK_EQUAL(lexer.getCurrentColumn(), 2);
        BOOST_CHECK_EQUAL(lexer.getCurrentLine(), 2);

    }

    BOOST_AUTO_TEST_CASE(recognise_first_token) {

        const std::string someTextString = " 12";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        auto optionalToken = lexer.getNextToken();

        BOOST_REQUIRE(optionalToken.is_initialized());

        auto token = optionalToken.get();

        BOOST_CHECK(token.getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK_EQUAL(token.getDoubleValue(), 12);
        BOOST_CHECK_THROW(token.getTextValue(), std::logic_error);

    }

    BOOST_AUTO_TEST_CASE(check_file_end) {
        const std::string someTextString = " // ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        auto optionalToken = lexer.getNextToken();

        BOOST_CHECK_EQUAL(optionalToken.is_initialized(), false);
    }

    BOOST_AUTO_TEST_CASE(get_two_tokens) {

        const std::string someTextString = " 12 12";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        auto optionalToken = lexer.getNextToken();

        BOOST_REQUIRE(optionalToken.is_initialized());

        auto token = optionalToken.get();

        BOOST_CHECK(token.getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK_EQUAL(token.getDoubleValue(), 12);


        auto secondOptionalToken = lexer.getNextToken();

        BOOST_REQUIRE(secondOptionalToken.is_initialized());

        auto secondToken = secondOptionalToken.get();

        BOOST_CHECK(secondToken.getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK_EQUAL(secondToken.getDoubleValue(), 12);

    }

    BOOST_AUTO_TEST_CASE(check_text_literal) {
        const std::string someTextString = " \"hello\" ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);
        auto optionalToken = lexer.getNextToken();

        BOOST_REQUIRE(optionalToken.is_initialized());

        auto token = optionalToken.get();

        BOOST_CHECK(token.getType() == TokenType::TEXT_LITERAL);
        BOOST_CHECK_EQUAL(token.getTextValue(), "hello");
    }

    BOOST_AUTO_TEST_CASE(check_text_literal_should_throw) {
        const std::string someTextString = " \"hello ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        BOOST_CHECK_THROW(lexer.getNextToken(), std::invalid_argument);

    }


    BOOST_AUTO_TEST_CASE(should_return_last_keyword) {
        const std::string someTextString = " for";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        auto optionalToken = lexer.getNextToken();

        BOOST_REQUIRE(optionalToken.is_initialized());

        auto token = optionalToken.get();

        BOOST_CHECK(token.getType() == TokenType::FOR);

    }

    BOOST_AUTO_TEST_CASE(should_return_last_identifier) {
        const std::string someTextString = " for1";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        auto optionalToken = lexer.getNextToken();

        BOOST_REQUIRE(optionalToken.is_initialized());

        auto token = optionalToken.get();

        BOOST_CHECK(token.getType() == TokenType::IDENTIFIER);
        BOOST_CHECK_EQUAL(token.getTextValue(), "for1");


    }

    BOOST_AUTO_TEST_CASE(should_throw_invalid_number) {
        const std::string someTextString = " 1.1.1";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);

        BOOST_CHECK_THROW(lexer.getNextToken(), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(parse_several_tokens) {

        const std::string someTextString = " for i in Range(1, 2) { if i == 10 { System.print(true)}} ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);


        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::FOR);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IN);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::COMMA);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IF);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::EQUAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::DOT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::TRUE);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_RIGHT);


        BOOST_CHECK_EQUAL(lexer.getNextToken().is_initialized(), false);


    }

    BOOST_AUTO_TEST_CASE(parse_several_tokens_1) {

        const std::string someTextString = " for i in Range(1, 2) { if i == 10 { System.print( \" Hello \" )}} ";
        std::stringstream stream(someTextString);

        Lexer lexer(stream);


        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::FOR);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IN);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::COMMA);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IF);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::EQUAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::NUM_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::DOT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::IDENTIFIER);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_LEFT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::TEXT_LITERAL);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::PARENTHESIS_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_RIGHT);
        BOOST_CHECK(lexer.getNextToken().value().getType() == TokenType::CBRACKET_RIGHT);


        BOOST_CHECK_EQUAL(lexer.getNextToken().is_initialized(), false);


    }



BOOST_AUTO_TEST_SUITE_END()

#endif // BOOST_TEST_DYN_LINK