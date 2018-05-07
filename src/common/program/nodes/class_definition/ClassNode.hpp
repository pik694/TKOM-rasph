//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_CLASSNODE_HPP
#define RASPH_CLASSNODE_HPP

#include <common/program/ProgramNode.hpp>
#include "members/ClassMemberNode.hpp"
#include <string>
#include <vector>

namespace rasph::common::program::nodes {
    class ClassNode : public ProgramNode{
    public:
        explicit ClassNode(const std::string &name);

        const std::string &getName() const;
        void addNode(std::unique_ptr<ClassMemberNode> member);

        const std::vector<std::unique_ptr<ClassMemberNode>> &getMembers() const;

        ~ClassNode() override  = default;

    private:
        const std::string name_;
        std::vector<std::unique_ptr<ClassMemberNode>> members_;

    };
}

#endif //RASPH_CLASSNODE_HPP
