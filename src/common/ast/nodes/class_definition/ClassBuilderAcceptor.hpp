//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_CLASSBUILDERACCEPTOR_HPP
#define RASPH_CLASSBUILDERACCEPTOR_HPP

#include <interpreter/environment/class/ClassBuilder.hpp>

namespace rasph::common::ast::nodes{

    class ClassBuilderAcceptor {
    public:

        virtual void accept(rasph::interpreter::environment::ClassBuilder&) = 0;

        virtual ~ClassBuilderAcceptor() = default;
    };

}

#endif //RASPH_CLASSBUILDERACCEPTOR_HPP
