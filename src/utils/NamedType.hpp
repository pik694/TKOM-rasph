//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_NAMEDTYPE_HPP
#define RASPH_NAMEDTYPE_HPP

#include <algorithm>

namespace rasph::utils {
    template<typename T, typename Parameter>
    class NamedType {
    public:
        explicit NamedType(T const &value) : value_(value) {}

        explicit NamedType(T &&value) : value_(std::move(value)) {}

        T &get() { return value_; }

        T const &get() const { return value_; }

    private:
        T value_;
    };
}

#endif //RASPH_NAMEDTYPE_HPP
