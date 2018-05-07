//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_SPECIALISEDNODESFACTORY_HPP
#define RASPH_SPECIALISEDNODESFACTORY_HPP

#include "Parser.hpp"
#include "traits.hpp"

namespace rasph::parser {

    template<typename T>
    class SpecialisedNodeFactory{
    public:
        SpecialisedNodeFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()();

    private:
        Parser& parser_;
    };

    template<>
    node_ptr_t SpecialisedNodeFactory<traits::class_definition>::operator()() {
        if (parser_.tokensBuffer_.empty()) return nullptr;
        return nullptr;
    }

}

#endif //RASPH_SPECIALISEDNODESFACTORY_HPP
