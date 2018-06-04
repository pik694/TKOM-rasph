//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_SYMBOL_HPP
#define RASPH_SYMBOL_HPP

#include <string>
#include <common/types/Object.hpp>

namespace rasph::interpreter::environment::symbols {

    class Symbol {
    public:

        explicit Symbol(const std::string &name, std::unique_ptr<rasph::common::types::Object> value);

        Symbol(Symbol const& other);

        common::types::Object  const& getValue() const;

        Symbol &operator=(Symbol &&symbol);

        const std::string &getName() const;

        virtual ~Symbol() = default;

    private:

        std::unique_ptr<const common::types::Object> value_;

        const std::string name_;
    };
}


#endif //RASPH_SYMBOL_HPP
