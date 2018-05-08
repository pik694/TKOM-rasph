//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_ATTRIBUTEMEMBERNODE_HPP
#define RASPH_ATTRIBUTEMEMBERNODE_HPP

#include "ClassMemberNode.hpp"

namespace rasph::common::ast::nodes {
    class AttributeMemberNode : public ClassMemberNode{
    public:
        AttributeMemberNode(const std::string &name) : ClassMemberNode(name){};
    };
}

#endif //RASPH_ATTRIBUTEMEMBERNODE_HPP
