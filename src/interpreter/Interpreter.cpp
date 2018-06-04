//
// Created by Piotr Żelazko on 04.06.2018.
//


#include "Interpreter.hpp"
#include "lexer/Lexer.h"
#include "parser/Parser.hpp"
#include <sstream>

using namespace rasph::interpreter;

Interpreter::Interpreter(std::istream &istream, std::ostream& ostream):istream_(istream), ostream_(ostream) {
    istream_ >> std::noskipws;
}

void Interpreter::operator()() {
    std::string code;

    ostream_ << ">";
    while (istream_ >> code){
        std::unique_ptr<lexer::Lexer> lexer = std::make_unique<lexer::Lexer>(
                std::make_unique<std::stringstream>(std::string(code))
        );

        parser::Parser parser(std::move(lexer));

        auto tree = parser.parse();

        try {
            tree->run();
        }catch (std::exception& e){
            std::cerr << "An error occurred: " << e.what() << std::endl;
        }
        ostream_ << ">";
    }
}
