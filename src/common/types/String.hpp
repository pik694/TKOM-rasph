//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_STRING_HPP
#define RASPH_STRING_HPP



#include "Object.hpp"
#include <string>

namespace rasph::common::types {
    class String : public Object, public visitors::AddVisitor{
    public:
        String(const std::string &value);

        const std::string &getValue() const;

        void setValue(const std::string &value_);

        explicit operator bool() const override;

        std::unique_ptr<String> clone() const;

        bool operator!() const override;

        bool operator<(Object const& object) const override;

        bool operator>(Object const& object) const override;

        std::unique_ptr<Object> operator+(Object const &object) const override;

        std::unique_ptr<Object> accept(visitors::AddVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::SubtractVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::MultiplyVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::DivideVisitor const &visitor) const override;

        std::unique_ptr<Object> add(String const &string) const override;

        std::unique_ptr<Object> add(Double const &aDouble) const override;


    private:
        String *copyImplementation() const override;

    private:
        std::string value_;
    };
}


#endif //RASPH_STRING_HPP
