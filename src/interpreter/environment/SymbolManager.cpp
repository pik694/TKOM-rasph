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

    std::lock_guard<std::mutex> guard(symbolsMutex_);

    if (methodCallArguments_ != nullptr){
        auto methodArgumentIt = methodCallArguments_->find(symbolName);
        if (methodArgumentIt != methodCallArguments_->end()){
            return Symbol(methodArgumentIt->second);
        }
    }

    if (classMembers_ != nullptr){
        auto classMemberIt= classMembers_->find(symbolName);
        if (classMemberIt != classMembers_->end()){
            return Symbol(classMemberIt->second);
        }
    }

    auto symbolIt = symbols_.find(symbolName);
    if (symbolIt != symbols_.end())
        return Symbol(symbolIt->second);

    throw std::out_of_range("Could not find symbol: " + symbolName);
}

void SymbolManager::saveSymbol(symbols::Symbol&& symbol) {

    std::lock_guard<std::mutex> guard(symbolsMutex_);

    if (methodCallArguments_ != nullptr && methodCallArguments_->find(symbol.getName()) != methodCallArguments_->end())
        methodCallArguments_->at(symbol.getName()) = std::move(symbol);

    else if ( classMembers_!= nullptr && classMembers_->find(symbol.getName()) != classMembers_->end())
        classMembers_->at(symbol.getName()) = std::move(symbol);

    else if (symbols_.find(symbol.getName()) == symbols_.end())
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

void SymbolManager::setClassMembers(std::unordered_map<std::string, Symbol> *classMembers) {
    SymbolManager::classMembers_ = classMembers;
}

void SymbolManager::setMethodCallArguments(std::unordered_map<std::string, Symbol> *methodCallArguments) {
    SymbolManager::methodCallArguments_ = methodCallArguments;
}

void SymbolManager::unsetMethodCallArguments() {
    methodCallArguments_ = nullptr;
}

void SymbolManager::unsetClassMembers() {
    classMembers_ = nullptr;
}
