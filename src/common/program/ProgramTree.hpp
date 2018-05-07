//
// Created by Piotr Żelazko on 06.05.2018.
//

#ifndef RASPH_PROGRAMTREE_HPP
#define RASPH_PROGRAMTREE_HPP

#include <vector>
#include "ProgramNode.hpp"

namespace rasph::common::program {
    class ProgramTree {
    public:
        void add(std::unique_ptr<ProgramNode> node);

        bool isEmpty();

    private:
        std::vector<std::unique_ptr<ProgramNode>> atomicNodes_;
    };

}

#endif //RASPH_PROGRAMTREE_HPP
