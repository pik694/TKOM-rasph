//
// Created by Piotr Żelazko on 08.05.2018.
//

#ifndef RASPH_METHODMEMBERNODE_HPP
#define RASPH_METHODMEMBERNODE_HPP

#include <vector>
#include <list>
#include "ClassMemberNode.hpp"
#include <algorithm>
#include <common/ast/nodes/statements/StatementNode.hpp>

namespace rasph::common::ast::nodes {
    class MethodMemberNode : public ClassMemberNode {
    public:
        MethodMemberNode(const std::string &name) : ClassMemberNode(name) {}

        const std::vector<const std::string> &getParameters() const {
            return parameters_;
        }

        void addParameter(const std::string& paramName){

            if (std::find(parameters_.begin(), parameters_.end(), paramName) == parameters_.end()){
                parameters_.push_back(paramName);
            }
            else{
                throw std::invalid_argument("Given parameter already exists: " + paramName);
            }

        }

        void addStatement(std::unique_ptr<nodes::StatementNode> statement){
            statements_.push_back(std::move(statement));
        }

        const std::list<std::unique_ptr<nodes::StatementNode>> &getStatements() const {
            return statements_;
        }

    private:
        std::vector<const std::string> parameters_;
        std::list<std::unique_ptr<nodes::StatementNode>> statements_;

    };
}


#endif //RASPH_METHODMEMBERNODE_HPP
