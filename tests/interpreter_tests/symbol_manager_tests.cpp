//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <interpreter/environment/SymbolManager.hpp>

using namespace rasph::interpreter::environment;

BOOST_AUTO_TEST_SUITE(symbol_manager_test)

    BOOST_AUTO_TEST_CASE(should_return_symbol) {

        symbols::Symbol symbol("a");

        SymbolManager::getInstance().saveSymbol(std::move(symbol));

        BOOST_CHECK(SymbolManager::getInstance().contains("a"));

        BOOST_CHECK_NO_THROW(SymbolManager::getInstance().getSymbol("a"));


    }




BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK