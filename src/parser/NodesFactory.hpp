//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_NODESFACTORY_HPP
#define RASPH_NODESFACTORY_HPP

#include "Parser.hpp"
#include "SpecialisedNodesFactory.hpp"

namespace rasph::parser {

    template <typename... Args>
    class NodesFactory {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()(){
            return nullptr;
        }

    private:
        Parser& parser_;
    };

    template <typename T, typename... Args>
    class NodesFactory<T, Args... > {
    public:
        NodesFactory(Parser &parser_) : parser_(parser_) {}

        node_ptr_t operator()(){
            auto result = SpecialisedNodeFactory<T>(parser_)();
            return result ? std::move(result) : NodesFactory<Args...>(parser_)();
        }

    private:
        Parser& parser_;
    };


}




#endif //RASPH_NODESFACTORY_HPP
