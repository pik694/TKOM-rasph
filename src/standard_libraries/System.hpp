//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_SYSTEM_HPP
#define RASPH_SYSTEM_HPP

#include <string>

namespace rasph::standard_libraries {
    class System {
        static void print(const std::string text);
        static void println(const std::string text);
    };
}


#endif //RASPH_SYSTEM_HPP
