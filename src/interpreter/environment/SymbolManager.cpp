//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "SymbolManager.hpp"

using namespace rasph::interpreter::environment;
using namespace rasph::interpreter::environment::symbols;

SymbolManager* SymbolManager::instance_ = nullptr;

SymbolManager &SymbolManager::getInstance() {
    if (instance_ == nullptr)
        instance_ = new SymbolManager();

    return *instance_;

}



symbols::Symbol SymbolManager::getSymbol(const std::string& symbolName) {

    symbolsMutex_.lock();

    auto symbolIt = symbols_.find(symbolName);

    symbolsMutex_.unlock();

    if (symbolIt != symbols_.end())
        return Symbol(symbolIt->second);

    throw std::out_of_range("Could not find symbol: " + symbolName);
}

void SymbolManager::saveSymbol(symbols::Symbol&& symbol) {

    std::lock_guard<std::mutex> guard(symbolsMutex_);

    if (symbols_.find(symbol.getName()) == symbols_.end())
        symbols_.emplace(std::make_pair(std::string(symbol.getName()), std::move(symbol)));

    else
        symbols_.at(symbol.getName()) = std::move(symbol);

}

bool SymbolManager::contains(std::string const &symbolName) {


    symbolsMutex_.lock();

    auto symbolIt = symbols_.find(symbolName);

    symbolsMutex_.unlock();

    return symbolIt != symbols_.end();

}
