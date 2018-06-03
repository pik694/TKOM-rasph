//
// Created by Piotr Żelazko on 04.06.2018.
//

#include "Interpreter.hpp"
#include "lexer/Lexer.h"
#include "parser/Parser.hpp"

using namespace rasph::interpreter;


Interpreter::Interpreter(std::istream &istream):istream_(istream) {
    istream_ >> std::noskipws;
}

void Interpreter::operator()() {
    std::string code;
    while (istream_ >> code){
        auto lexer = std::make_unique<lexer::Lexer>(
                std::make_unique<std::stringstream>(code)
        );

        parser::Parser parser(std::move(lexer));

        auto tree = parser.parse();

        try {
            tree->run();
        }catch (std::exception& e){
            std::cerr << "An error occurred: " << e.what() << std::endl;
        }
    }
}
