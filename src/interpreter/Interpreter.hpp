//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_INTERPRETER_HPP
#define RASPH_INTERPRETER_HPP


#include <istream>


namespace rasph::interpreter {
    class Interpreter {
    public:

        Interpreter(std::istream &istream);

        void operator()();

    private:

        std::istream &istream_;

    };
}


#endif //RASPH_INTERPRETER_HPP
