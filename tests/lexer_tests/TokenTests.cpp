// //
// // Created by Piotr Żelazko on 23.04.2018.
// //

// #include <boost/test/unit_test.hpp>

// #define BOOST_TEST_DYN_LINK

// #ifdef BOOST_TEST_DYN_LINK

// #include "lexer/Lexer.h"
// #include "common/tokens.h"

// #include <string>
// #include <algorithm>

// using namespace rasph::lexer;
// using namespace rasph::common::tokens;


// BOOST_AUTO_TEST_SUITE(lexer_test_suite)


//     struct mapping_t {

//         mapping_t(const std::string &token_str, const lex::token_def<> &token_def) : token_str(token_str),
//                                                                                      token_def(token_def) {}

//         const std::string &token_str;
//         const lex::token_def<> &token_def;
//     };


//     void check_all_tokens_recognition(std::vector<mapping_t> tokens) {

//         std::for_each(tokens.begin(), tokens.end(), [](mapping_t token) {
//             std::istringstream inputStream(token.token_str);
//             Lexer lexer(inputStream);
//             BOOST_REQUIRE_EQUAL(lexer.nextToken().id(), token.token_def.id());
//         });
//     }

//     BOOST_AUTO_TEST_CASE(check_whether_all_tokens_are_recognised_properly) {


//         check_all_tokens_recognition({
// //                                             {"if", if_token},
// //                                             {"else", else_token},
// //                                             {"for", for_token},
// //                                             {"class", class_token},
// //                                             {"func", func_token},
// //                                             {"var", var_token},
// //                                             {"return", return_token},
// //                                             {"->", arrow_token},
// //                                             {"event", event_token},
// //                                             {"handle", handle_token},
// //                                             {"with", with_token},
// //                                             {"in", in_token},
// //                                             {".", dot_token},
// //
// //                                             {"every", every_token},
// //                                             {"m", month_token},
// //                                             {"w", week_token},
// //                                             {"d", day_token},
// //                                             {"h", hour_token},
// //                                             {"min", min_token},
// //                                             {"sec", sec_token},
// //                                             {"ms", ms_token},
// //
// //                                             {"=", assign_token},
// //                                             {"+", plus_token},
// //                                             {"-", minus_token},
// //                                             {"/", div_token},
// //                                             {"*", multiply_token},
// //
// //                                             {"==", equality_token},
// //                                             {"!=", inequality_token},
// //                                             {"<", less_token},
// //                                             {"<=", less_eq_token},
// //                                             {">", greater_token},
// //                                             {">=", greater_eq_token},
// //
// //                                             {"or", or_token},
// //                                             {"and", and_token},
// //                                             {"!", not_token},
// //
// ////                                             {"(", parent_left_token},
// ////                                             {")", parent_right_token},
// ////                                             {"{", bracket_left_token},
// ////                                             {"}", bracket_right_token}
// //
// //                                             {"true", true_token},
// //                                             {"on", true_token},
// //                                             {"false", false_token},
// //                                             {"off", false_token},
// //
// //                                             {"_ident", identifier_token},
// //                                             {"ident", identifier_token},
// //                                             {"IdEnt5q", identifier_token},
// //                                             {"IdEnt_5q", identifier_token},
// //                                             {"IdEnt_5q", identifier_token},
// //
// //                                             {"1.1", const_number_token},
// //                                             {"0.1", const_number_token},
// //                                             {"0.0", const_number_token},
// //                                             {"0", const_number_token},
// //                                             {"9", const_number_token},
// //
// ////                                             {"\"const string\"", const_string_token}
// ////                                             {"//", comment_start_token}
//                                              {"\040", space_character_token},
// //                                             {"\n", new_line_token}

//                                      });


//     }


// BOOST_AUTO_TEST_SUITE_END()

// #endif // BOOST_TEST_DYN_LINK
