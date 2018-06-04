//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <interpreter/environment/SymbolManager.hpp>
#include <common/types/Double.hpp>


using namespace rasph::interpreter::environment;
using namespace rasph::common::types;


BOOST_AUTO_TEST_SUITE(symbol_manager_test)

    BOOST_AUTO_TEST_CASE(should_return_symbol) {

        auto value = std::make_unique<rasph::common::types::Double>(1.0);
        symbols::Symbol symbol("a", std::move(value));

        SymbolManager::getInstance().saveSymbol(std::move(symbol));

        BOOST_CHECK(SymbolManager::getInstance().contains("a"));

        BOOST_CHECK_NO_THROW(SymbolManager::getInstance().getSymbol("a"));


    }

    BOOST_AUTO_TEST_CASE(should_change_mapped_value) {

        auto value = std::make_unique<Double>(1.0);
        symbols::Symbol symbol("a", std::move(value));

        auto newValue = std::make_unique<Double>(2.0);
        symbols::Symbol newSymbol("a", std::move(newValue));

        SymbolManager::getInstance().saveSymbol(std::move(symbol));


        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 1.0);

        SymbolManager::getInstance().saveSymbol(std::move(newSymbol));

        BOOST_CHECK_EQUAL(
                dynamic_cast<Double const &>(SymbolManager::getInstance().getSymbol("a").getValue()).getValue(), 2.0);

    }


BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK