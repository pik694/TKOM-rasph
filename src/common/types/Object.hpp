//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_OBJECT_HPP
#define RASPH_OBJECT_HPP

#include <memory>

namespace rasph::common::types {
    class Object {
    public:

        virtual explicit operator bool() const = 0;

        virtual bool operator!() const = 0;

        virtual bool acceptLessComparison(Object&) = 0;
        virtual bool acceptGreaterComparison(Object&) = 0;
        

        std::unique_ptr<Object> clone() const {
            return std::unique_ptr<Object>(this->copyImplementation());
        }

        virtual ~Object() = default;

        virtual bool operator<(Object&) const = 0;
        virtual bool operator>(Object&) const = 0;
        virtual bool operator<=(Object&) const = 0;
        virtual bool operator>=(Object&) const = 0;


    private:
        virtual Object* copyImplementation() const = 0;
    };
}


#endif //RASPH_OBJECT_HPP
