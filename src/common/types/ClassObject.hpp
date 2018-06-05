//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_CLASSOBJECT_HPP
#define RASPH_CLASSOBJECT_HPP

#include <interpreter/environment/class/ClassDefinition.hpp>
#include <interpreter/environment/symbols/Symbol.hpp>
#include "Object.hpp"

namespace rasph::common::types {
    class ClassObject : public Object{
    public:
        ClassObject(const interpreter::environment::ClassDefinition &classDefinition);

        explicit operator bool() const override;

        bool operator!() const override;

        bool operator==(Object const &object) const override;

        bool operator<(Object const &object) const override;

        bool operator>(Object const &object) const override;

        std::unique_ptr<Object> accept(visitors::AddVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::SubtractVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::MultiplyVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::DivideVisitor const &visitor) const override;

        std::unique_ptr<Object> valueOfMember(const std::string& name) const;

        std::unique_ptr<Object> executeMehtod(const std::string& name);

    private:
        Object *copyImplementation() const override;

    private:

        const interpreter::environment::ClassDefinition& classDefinition_;
        std::unordered_map<std::string, interpreter::environment::symbols::Symbol> symbols_;
    };
}


#endif //RASPH_CLASSOBJECT_HPP
