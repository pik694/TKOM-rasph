//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_OBJECT_HPP
#define RASPH_OBJECT_HPP

#include <memory>
#include "OperatorVisitor.hpp"

namespace rasph::common::types {
    class Object {
    public:

        virtual explicit operator bool() const = 0;

        virtual bool operator!() const = 0;

        std::unique_ptr<Object> clone() const {
            return std::unique_ptr<Object>(this->copyImplementation());
        }

        virtual ~Object() = default;

        virtual bool operator<(Object const &) const = 0;

        virtual bool operator>(Object const &) const = 0;

        virtual bool operator<=(Object const &object) const {
            return !(*this > object);
        }

        virtual bool operator>=(Object const &object) const {
            return !(*this < object);
        }


        virtual std::unique_ptr<Object> operator+(Object const &) const {
            throw std::runtime_error("This operator cannot be applied to object of this type");
        }

        virtual std::unique_ptr<Object> operator-(Object const &) const {
            throw std::runtime_error("This operator cannot be applied to object of this type");
        }


        virtual std::unique_ptr<Object> operator*(Object const &) const {
            throw std::runtime_error("This operator cannot be applied to object of this type");
        }

        virtual std::unique_ptr<Object> operator/(Object const &) const {
            throw std::runtime_error("This operator cannot be applied to object of this type");
        }

        virtual std::unique_ptr<Object> accept(visitors::AddVisitor const &) const = 0;

        virtual std::unique_ptr<Object> accept(visitors::SubtractVisitor const &) const = 0;

        virtual std::unique_ptr<Object> accept(visitors::MultiplyVisitor const &) const = 0;

        virtual std::unique_ptr<Object> accept(visitors::DivideVisitor const &) const = 0;


    private:
        virtual Object *copyImplementation() const = 0;
    };
}


#endif //RASPH_OBJECT_HPP
