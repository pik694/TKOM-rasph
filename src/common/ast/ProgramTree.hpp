//
// Created by Piotr Żelazko on 06.05.2018.
//

#ifndef RASPH_PROGRAMTREE_HPP
#define RASPH_PROGRAMTREE_HPP

#include <vector>
#include "ProgramNode.hpp"

namespace rasph::common::ast {
    class ProgramTree {
    public:
        void add(std::unique_ptr<ProgramNode> node);

        const std::vector<std::shared_ptr<ProgramNode>> &getNodes() const;

        bool isEmpty();

    private:
        std::vector<std::shared_ptr<ProgramNode>> atomicNodes_;
    };

}

#endif //RASPH_PROGRAMTREE_HPP
