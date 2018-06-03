//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_STRING_HPP
#define RASPH_STRING_HPP

#include <string>
#include "Object.hpp"

namespace rasph::common::types {
    class String : public Object {
    public:
        String(const std::string &value);

        const std::string &getValue() const;

        void setValue(const std::string &value_);

    private:
        std::string value_;
    };
}


#endif //RASPH_STRING_HPP
