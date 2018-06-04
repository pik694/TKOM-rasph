//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_METHODCALLNODE_HPP
#define RASPH_METHODCALLNODE_HPP


#include <common/ast/nodes/assignables/AssignableNode.hpp>

namespace rasph::common::ast::nodes {
    class ClassMemberCall : public  AssignableNode {
    public:
        ClassMemberCall(const std::string &object_, const std::string &member_) : object_(object_), member_(member_) {}


        std::unique_ptr<types::Object> value() override {
            //TODO
            throw std::runtime_error("Not implemented yet");
        }

    private:
        const std::string& object_;
        const std::string& member_;
    };
}

#endif //RASPH_METHODCALLNODE_HPP
