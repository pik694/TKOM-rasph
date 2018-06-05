//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_EVENTMEMBERNODE_HPP
#define RASPH_EVENTMEMBERNODE_HPP

#include "ClassMemberNode.hpp"

namespace rasph::common::ast::nodes {
    class EventMemberNode : public ClassMemberNode{
    public:
        EventMemberNode(const std::string &name) : ClassMemberNode(name) {}

        void accept(interpreter::environment::ClassBuilder& builder) override {
            builder.addElement(*this);
        }

    };
}



#endif //RASPH_EVENTMEMBERNODE_HPP
