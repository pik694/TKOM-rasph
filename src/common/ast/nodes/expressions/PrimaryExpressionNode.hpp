//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_PRIMARYEXPRESSIONNODE_HPP
#define RASPH_PRIMARYEXPRESSIONNODE_HPP

namespace rasph::common::ast::nodes {
    class PrimaryExpressionNode : public AssignableNode {
    public:
        PrimaryExpressionNode(std::unique_ptr<AssignableNode> expression_) : expression_(std::move(expression_)) {}

        void execute() override {
            expression_->execute();
        }

        std::unique_ptr<types::Object> value() override {
            return expression_->value();
        }

    private:
        std::unique_ptr<nodes::AssignableNode> expression_;
    };
}


#endif //RASPH_PRIMARYEXPRESSIONNODE_HPP
