//
// Created by Piotr Żelazko on 03.06.2018.
//

#ifndef RASPH_DOUBLE_HPP
#define RASPH_DOUBLE_HPP

#include "Object.hpp"
#include "OperatorVisitor.hpp"

namespace rasph::common::types {
    class Double : public Object, public visitors::AddVisitor, public visitors::SubtractVisitor, public visitors::MultiplyVisitor, public visitors::DivideVisitor {
    public:
        Double(double value);

        double getValue() const;

        void setValue(double value_);

        explicit operator bool() const override;

        std::unique_ptr<Double> clone () const;

        bool operator<(Object const& object) const override;

        bool operator>(Object const& object) const override;

        std::unique_ptr<Object> operator+(Object const &object) const override;

        std::unique_ptr<Object> operator-(Object const &object) const override;

        std::unique_ptr<Object> operator*(Object const &object) const override;

        std::unique_ptr<Object> operator/(Object const &object) const override;


        bool operator!() const override;

        std::unique_ptr<Object> add(String const &string) const override;

        std::unique_ptr<Object> add(Double const &aDouble) const override;

        std::unique_ptr<Object> subtract(Double const &aDouble) const override;

        std::unique_ptr<Object> multiply(Double const &aDouble) const override;

        std::unique_ptr<Object> divide(Double const &aDouble) const override;

        std::unique_ptr<Object> accept(visitors::AddVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::SubtractVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::MultiplyVisitor const &visitor) const override;

        std::unique_ptr<Object> accept(visitors::DivideVisitor const &visitor) const override;

        bool operator==(Object const &object) const override;

    private:

        Double *copyImplementation() const override;

        double value_;
    };
}


#endif //RASPH_DOUBLE_HPP
