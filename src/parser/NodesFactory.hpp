//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_NODESFACTORY_HPP
#define RASPH_NODESFACTORY_HPP

#include "Parser.hpp"

namespace rasph::parser {

    using common::tokens::TokenType;
    using namespace common::ast;

    template<typename... Args>
    class NodesFactory {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()() {

            return parser_.tryParse<>();
        }

    private:
        Parser &parser_;
    };

    template<typename T, typename... Args>
    class NodesFactory<T, Args...> {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()() {
            auto result = parser_.tryParse<T>();
            return result ? std::move(result) : parser_.tryParse<Args...>();
        }

    private:
        Parser &parser_;
    };

}


#endif //RASPH_NODESFACTORY_HPP
