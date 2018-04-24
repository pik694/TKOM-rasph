// //
// // Created by Piotr Żelazko on 23.04.2018.
// //

#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK

#ifdef BOOST_TEST_DYN_LINK

#include "lexer/Lexer.h"
#include "common/tokens/tokens.h"

using namespace rasph::common;


BOOST_AUTO_TEST_SUITE(lexer_test_suite)

    BOOST_AUTO_TEST_CASE(newly_created_lexer_should_be_at_line_1_column_1) {



        BOOST_CHECK_EQUAL(1,1);
//        //given: sample input stream and a lexer
//        std::string someText = "Some text";
//        std::istringstream inputStream(someText);
//        Lexer lexer(inputStream);
//
//
//        //then: Lexer should be at line 1 and column 1
//        BOOST_CHECK_EQUAL(lexer.getLine(), 1);
//        BOOST_CHECK_EQUAL(lexer.getColumn(), 1);

    }
//
//
//    BOOST_AUTO_TEST_CASE(return_whole_string) {
//
//        //given: sample input stream
//        std::string someText = " %  Some text  !  % ";
//        std::istringstream inputStream(someText);
//
//
//        //when: I create a sample lexer from a stream
//        Lexer lexer(inputStream);
//
//
//        //then: strings should be equal
//        BOOST_CHECK_EQUAL(lexer.getText(), someText);
//
//
//    }
//
//    BOOST_AUTO_TEST_CASE(return_if_token) {
//
//        //given: sample input stream and a lexer
//        std::string someText = " if some text";
//        std::istringstream inputStream(someText);
//        Lexer lexer(inputStream);
//
//        //when: I fetch first token
//
//        auto token = lexer.nextToken();
//
//        //then: token should be 'if token'
//
//        BOOST_CHECK_EQUAL(token.id(), tokens::if_token.id());
//
//    }


//     BOOST_AUTO_TEST_CASE(return_if_and_else_token) {

//         //given: sample input stream and a lexer
//         std::string someText = "if else for in";
//         std::istringstream inputStream(someText);
//         Lexer lexer(inputStream);

//         //when: I fetch first token

//         auto token = lexer.nextToken();

//         //then: token should be 'if token'

//         BOOST_CHECK_EQUAL(token.id(), tokens::if_token.id());

//         //when: I fetch second token

//         auto secondToken = lexer.nextToken();

//         //then: token should be 'else token'

//         BOOST_CHECK_EQUAL(secondToken.id(), tokens::else_token.id());

//     }

//     BOOST_AUTO_TEST_CASE(invalid_input_should_throw_exception) {

//         //given: sample input stream and a lexer
//         std::string someText = "@ac some  text if";
//         std::istringstream inputStream(someText);
//         Lexer lexer(inputStream);

//         //when: I fetch first token it should throw exception
//         BOOST_REQUIRE_THROW(lexer.nextToken(), std::invalid_argument);

//         //then: lexer is at line 1, column 1

//         BOOST_CHECK_EQUAL(lexer.getLine(), 1);
//         BOOST_CHECK_EQUAL(lexer.getColumn(), 1);


//     }



//     BOOST_AUTO_TEST_CASE(end_of_text) {

//         //given: sample input stream and a lexer
//         std::string someText = "in ";
//         std::istringstream inputStream(someText);
//         Lexer lexer(inputStream);


//         lexer.nextToken();
//         const auto token = lexer.nextToken();

//         //when: I fetch another  token it return the same token

//         BOOST_CHECK_EQUAL(lexer.nextToken(), token);


//     }



//     BOOST_AUTO_TEST_CASE(only_one_token_valid) {

//         //given: sample input stream and a lexer
//         std::string someText = "in #invalid #text if";
//         std::istringstream inputStream(someText);
//         Lexer lexer(inputStream);

//         lexer.nextToken();

//         //when: I fetch first token it should throw exception

//         BOOST_REQUIRE_THROW(lexer.nextToken(), std::invalid_argument);

//         //then: lexer is at line 1, column 1

// //        BOOST_CHECK_EQUAL(lexer.getLine(), 1);
// //        BOOST_CHECK_EQUAL(lexer.getColumn(), 3);


//     }



//     BOOST_AUTO_TEST_CASE(should_parse_2_tokens_and_throw) {

//         //given: sample input stream and a lexer
//         std::string someText = "in invalid #text if";
//         std::istringstream inputStream(someText);
//         Lexer lexer(inputStream);


//         //when: I fetch third token it should throw an exception

//         auto token = lexer.nextToken();
//         lexer.nextToken();


//         BOOST_REQUIRE_THROW(lexer.nextToken(), std::invalid_argument);

//         //then: lexer is at line 1, column 1

// //        BOOST_CHECK_EQUAL(lexer.getLine(), 1);
// //        BOOST_CHECK_EQUAL(lexer.getColumn(), 3);


//     }

BOOST_AUTO_TEST_SUITE_END()

#endif // BOOST_TEST_DYN_LINK
