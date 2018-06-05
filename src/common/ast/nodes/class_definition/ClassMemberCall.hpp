//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_METHODCALLNODE_HPP
#define RASPH_METHODCALLNODE_HPP


#include <common/ast/nodes/assignables/AssignableNode.hpp>
#include <interpreter/environment/SymbolManager.hpp>
#include <common/types/ClassObject.hpp>

namespace rasph::common::ast::nodes {
    class ClassMemberCall : public  AssignableNode {
    public:
        ClassMemberCall(std::string object_, std::string member_) : object_(std::move(object_)), member_(std::move(member_)) {}


        std::unique_ptr<types::Object> value() override {

                auto symbol = interpreter::environment::SymbolManager::getInstance().getSymbol(object_);

                auto& object = dynamic_cast<types::ClassObject const&>(symbol.getValue());

                return object.valueOfMember(member_);

        }

        const std::string &getObject() const {
            return object_;
        }

        const std::string &getMember() const {
            return member_;
        }

    protected:
        const std::string object_;
        const std::string member_;
    };
}

#endif //RASPH_METHODCALLNODE_HPP
