//
// Created by Piotr Żelazko on 09.05.2018.
//

#ifndef RASPH_PRIMARYEXPRESSIONNODE_HPP
#define RASPH_PRIMARYEXPRESSIONNODE_HPP

namespace rasph::common::ast::nodes {
    class PrimaryExpressionNode : public ProgramNode{
    public:
        PrimaryExpressionNode(std::unique_ptr<AssignableNode> expression_) : expression_(std::move(expression_)) {}

    private:
        std::unique_ptr<nodes::AssignableNode> expression_;
    };
}


#endif //RASPH_PRIMARYEXPRESSIONNODE_HPP
