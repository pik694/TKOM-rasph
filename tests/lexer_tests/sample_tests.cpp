//
// Created by Piotr Żelazko on 16.04.2018.
//

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_DYN_LINK

#ifdef BOOST_TEST_DYN_LINK

#include "lexer/Lexer.h"

BOOST_AUTO_TEST_SUITE(lexer_test_suite)

    BOOST_AUTO_TEST_CASE(sample_test_case) {

        BOOST_CHECK_EQUAL(1,1);
        
    }

BOOST_AUTO_TEST_SUITE_END()

#endif // BOOST_TEST_DYN_LINK
