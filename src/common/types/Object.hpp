//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_OBJECT_HPP
#define RASPH_OBJECT_HPP

namespace rasph::common::types {
    class Object {
    public:

        virtual explicit operator bool() const = 0;

        virtual bool operator!() const = 0;

        virtual ~Object() = default;
    };
}


#endif //RASPH_OBJECT_HPP
