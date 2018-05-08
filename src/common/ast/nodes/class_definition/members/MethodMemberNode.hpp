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
        explicit MethodMemberNode(const std::string &name);

        const std::vector<std::unique_ptr<int>> &getParameters() const;

        const std::list<std::unique_ptr<int>> &getStatements() const;

    private:
        std::vector<std::unique_ptr<int>> parameters_;
        std::list<std::unique_ptr<int>> statements_;

    };
}


#endif //RASPH_METHODMEMBERNODE_HPP
