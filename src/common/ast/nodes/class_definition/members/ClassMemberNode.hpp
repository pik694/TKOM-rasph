//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_CLASSMEMBERSNODE_HPP
#define RASPH_CLASSMEMBERSNODE_HPP


#include <common/ast/ProgramNode.hpp>
#include <string>
#include <common/ast/nodes/class_definition/ClassBuilderAcceptor.hpp>

namespace rasph::common::ast::nodes {
    class ClassMemberNode : public ProgramNode, public ClassBuilderAcceptor {
    public:
        explicit ClassMemberNode(std::string name): name_(std::move(name)){}

        const std::string &getName() const { return name_;}

        void execute() override {}

    private:
        const std::string name_;
    };
}


#endif //RASPH_CLASSMEMBERSNODE_HPP
