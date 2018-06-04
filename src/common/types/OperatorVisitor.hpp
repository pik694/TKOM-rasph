//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_OPERATORVISITOR_HPP
#define RASPH_OPERATORVISITOR_HPP

namespace rasph::common::types {

    class Object;

    class String;

    class Boolean;

    class Double;

    class ClassObject;

}
namespace rasph::common::types::visitors {

    class AddVisitor {
    public:

        virtual std::unique_ptr<Object> add(String const &) const;

        virtual std::unique_ptr<Object> add(Boolean const &) const;

        virtual std::unique_ptr<Object> add(ClassObject const &) const;

        virtual std::unique_ptr<Object> add(Double const &) const;

        virtual ~AddVisitor() = 0;


    };

    class SubtractVisitor {
    public:

        virtual std::unique_ptr<Object> subtract(String const &) const;

        virtual std::unique_ptr<Object> subtract(Boolean const &) const;

        virtual std::unique_ptr<Object> subtract(ClassObject const &) const;

        virtual std::unique_ptr<Object> subtract(Double const &) const;

        virtual ~SubtractVisitor() = 0;


    };

    class MultiplyVisitor {
    public:
        virtual std::unique_ptr<Object> multiply(String const &) const;

        virtual std::unique_ptr<Object> multiply(Boolean const &) const;

        virtual std::unique_ptr<Object> multiply(ClassObject const &) const;

        virtual std::unique_ptr<Object> multiply(Double const &) const;

        virtual ~MultiplyVisitor() = 0;

    };

    class DivideVisitor {
    public:
        virtual std::unique_ptr<Object> divide(String const &) const;

        virtual std::unique_ptr<Object> divide(Boolean const &) const;

        virtual std::unique_ptr<Object> divide(ClassObject const &) const;

        virtual std::unique_ptr<Object> divide(Double const &) const;

        virtual ~DivideVisitor() = 0;

    };

}

#endif //RASPH_OPERATORVISITOR_HPP
