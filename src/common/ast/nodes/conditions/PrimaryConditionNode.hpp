//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_PRIMARYCONDITIONNODE_HPP
#define RASPH_PRIMARYCONDITIONNODE_HPP


#include "ConditionNode.hpp"

namespace rasph::common::ast::nodes {
    class PrimaryConditionNode : public AssignableNode {
    public:
        PrimaryConditionNode(const bool inverted_, std::unique_ptr<AssignableNode> node_) :
                inverted_(inverted_),
                node_(std::move(node_)) {}


        std::unique_ptr<types::Object> value() override {

            auto value = node_->value();

            if (inverted_){
                return std::unique_ptr<types::Object>(new types::Boolean(!(*value)));
            }
            return std::move(value);

        }


    private:
        const bool inverted_;
        const std::unique_ptr<AssignableNode> node_;
    };
}

#endif //RASPH_PRIMARYCONDITIONNODE_HPP
