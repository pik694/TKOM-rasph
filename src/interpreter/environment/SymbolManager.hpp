//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_SYMBOLMANAGER_HPP
#define RASPH_SYMBOLMANAGER_HPP

#include <string>
#include <map>
#include <mutex>
#include <unordered_map>

#include "symbols/Symbol.hpp"

namespace rasph::interpreter::environment {
    class SymbolManager {
    public:
        SymbolManager(const SymbolManager &) = delete;

        static SymbolManager &getInstance();

        symbols::Symbol getSymbol(const std::string& symbolName);

        void setClassMembers(std::unordered_map<std::string, symbols::Symbol> *classMembers);

        void setMethodCallArguments(std::unordered_map<std::string, symbols::Symbol> *methodCallArguments);

        void unsetMethodCallArguments();
        void unsetClassMembers();

        void saveSymbol(symbols::Symbol&& symbol);

        bool contains(std::string const& symbolName);

        ~SymbolManager() = default;

    private:
        static SymbolManager *instance_;

        SymbolManager() = default;


        std::mutex symbolsMutex_;
        std::unordered_map<std::string, symbols::Symbol> symbols_;
        std::unordered_map<std::string, symbols::Symbol>* classMembers_ = nullptr;
        std::unordered_map<std::string, symbols::Symbol>* methodCallArguments_ = nullptr;


    };
}


#endif //RASPH_SYMBOLMANAGER_HPP
