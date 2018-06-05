//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_CLASSNODE_HPP
#define RASPH_CLASSNODE_HPP

#include <common/ast/ProgramNode.hpp>
#include "members/ClassMemberNode.hpp"
#include "ClassBuilderAcceptor.hpp"
#include <string>
#include <vector>
#include <interpreter/environment/class/ClassBuilder.hpp>

namespace rasph::common::ast::nodes {
    class ClassNode : public ProgramNode {
    public:
        explicit ClassNode(const std::string &name);

        const std::string &getName() const;
        void addNode(std::unique_ptr<ClassMemberNode> member);

        const std::vector<std::unique_ptr<ClassMemberNode>> &getMembers() const;

        void execute() override;

        ~ClassNode() override  = default;

    private:
        void build();

        const std::string name_;
        std::vector<std::unique_ptr<ClassMemberNode>> members_;

    };
}

#endif //RASPH_CLASSNODE_HPP
