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

        const symbols::Symbol& getSymbol(const std::string& symbolName);

        void saveSymbol(symbols::Symbol&& symbol);

        ~SymbolManager() = default;

    private:
        static SymbolManager *instance_;

        SymbolManager() = default;


        std::mutex symbolsMutex_;
        std::unordered_map<std::string, std::unique_ptr<symbols::Symbol>> symbols_;

    };
}


#endif //RASPH_SYMBOLMANAGER_HPP
