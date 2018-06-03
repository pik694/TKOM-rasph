//
// Created by Piotr Żelazko on 03.06.2018.
//

#include "SymbolManager.hpp"

using namespace rasph::interpreter::environment;
using namespace rasph::interpreter::environment::symbols;

SymbolManager &SymbolManager::getInstance() {
    if (instance_ == nullptr)
        instance_ = new SymbolManager();

    return *instance_;

}



const Symbol& SymbolManager::getSymbol(const std::string& symbolName) {

    symbolsMutex_.lock();

    auto symbolIt = symbols_.find(symbolName);

    symbolsMutex_.unlock();

    if (symbolIt != symbols_.end()) return *(symbolIt->second);

    throw std::out_of_range("Could not find symbol: " + symbolName);
}

void SymbolManager::saveSymbol(Symbol &&symbol) {

    std::lock_guard<std::mutex> guard(symbolsMutex_);

    //TODO

//    if (symbols_.find(symbol.getName()) != symbols_.end()){
//
////        symbols_.insert(std::make_pair(symbol.getName(), std::make_unique<Symbol>(std::move(symbol))));
//    }
//
//    else
//        symbols_.at(symbol.getName()) = std::make_unique<Symbol>(std::move(symbol));

}
