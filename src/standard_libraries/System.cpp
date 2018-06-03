//
// Created by Piotr Żelazko on 03.06.2018.
//

#include <string>
#include <iostream>
#include "System.hpp"


void rasph::standard_libraries::System::print(const std::string text) {
    std::cout << text;
}

void rasph::standard_libraries::System::println(const std::string text) {
    std::cout << text << std::endl;
}
