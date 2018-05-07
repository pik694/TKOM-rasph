//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_CLASSMEMBERSNODE_HPP
#define RASPH_CLASSMEMBERSNODE_HPP


#include <common/program/ProgramNode.hpp>
#include <string>

namespace rasph::common::program::nodes {
    class ClassMemberNode : public ProgramNode {
    public:
        ClassMemberNode(const std::string &name);

        const std::string &getName() const;

    private:
        const std::string name_;
    };
}


#endif //RASPH_CLASSMEMBERSNODE_HPP
