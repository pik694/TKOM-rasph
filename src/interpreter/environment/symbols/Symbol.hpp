//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_SYMBOL_HPP
#define RASPH_SYMBOL_HPP

#include <string>

namespace rasph::interpreter::environment::symbols {

    class Symbol {
    public:

        explicit Symbol(const std::string& name);

        const std::string &getName() const;

        virtual ~Symbol() = 0;

    private:
        const std::string name_;
    };
}


#endif //RASPH_SYMBOL_HPP
