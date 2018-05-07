//
// Created by Piotr Żelazko on 06.05.2018.
//

#include "ProgramTree.hpp"

using namespace rasph::common::program;

void ProgramTree::add(std::unique_ptr<ProgramNode> node) {
    atomicNodes_.push_back(std::move(node));
}


bool ProgramTree::isEmpty() {
    return atomicNodes_.empty();
}
