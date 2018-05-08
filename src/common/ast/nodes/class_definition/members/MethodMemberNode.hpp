//
// Created by Piotr Żelazko on 08.05.2018.
//

#ifndef RASPH_METHODMEMBERNODE_HPP
#define RASPH_METHODMEMBERNODE_HPP

#include <vector>
#include <list>
#include "ClassMemberNode.hpp"

namespace rasph::common::ast::nodes {
    class MethodMemberNode : public ClassMemberNode {
    public:
        MethodMemberNode(const std::string &name) : ClassMemberNode(name) {}

        const std::vector<std::unique_ptr<int>> &getParameters() const {
            return parameters_;
        }

        const std::list<std::unique_ptr<int>> &getStatements() const {
            return statements_;
        }

    private:
        std::vector<std::unique_ptr<int>> parameters_;
        std::list<std::unique_ptr<int>> statements_;

    };
}


#endif //RASPH_METHODMEMBERNODE_HPP
