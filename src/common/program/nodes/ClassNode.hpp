//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_CLASSNODE_HPP
#define RASPH_CLASSNODE_HPP

#include <common/program/ProgramNode.hpp>
#include <string>

namespace rasph::common::program::nodes {
    class ClassNode : public ProgramNode{
    public:
        ClassNode(const std::string &name);

        ~ClassNode() override  = default;

    private:
        const std::string name_;
    };
}

#endif //RASPH_CLASSNODE_HPP
