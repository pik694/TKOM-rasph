//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_METHODCALL_HPP
#define RASPH_METHODCALL_HPP

#include <string>
#include <list>
#include "ClassMemberCall.hpp"

namespace rasph::common::ast::nodes {
    class MethodCall : public ClassMemberCall {
    public:

        MethodCall(const std::string &object_, const std::string &member_) : ClassMemberCall(object_, member_) {}

        void addParameter(std::unique_ptr<AssignableNode> param){
            parameters_.push_back(std::move(param));
        }

    private:
        std::list<std::unique_ptr<AssignableNode>> parameters_;

    };
}

#endif //RASPH_METHODCALL_HPP
