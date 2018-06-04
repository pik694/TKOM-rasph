//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_ASSIGNABLENODE_HPP
#define RASPH_ASSIGNABLENODE_HPP

#include <common/ast/ProgramNode.hpp>
#include <common/types/Object.hpp>

namespace rasph::common::ast::nodes {

    class AssignableNode : public ProgramNode {
    public:
        virtual std::unique_ptr<types::Object> value() = 0;

    };

}
#endif //RASPH_ASSIGNABLENODE_HPP
