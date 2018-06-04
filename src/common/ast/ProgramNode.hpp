//
// Created by Piotr Żelazko on 07.05.2018.
//

#ifndef RASPH_PROGRAMNODE_HPP
#define RASPH_PROGRAMNODE_HPP

namespace rasph::common::ast {
    class ProgramNode {
    public:
        virtual void execute() = 0;
        virtual ~ProgramNode() = default;
    };
}


#endif //RASPH_PROGRAMNODE_HPP
