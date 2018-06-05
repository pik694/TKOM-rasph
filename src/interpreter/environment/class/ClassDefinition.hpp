//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_CLASSDEFINITION_HPP
#define RASPH_CLASSDEFINITION_HPP

#include <string>
#include <vector>
#include <utils/NamedType.hpp>

namespace rasph::interpreter::environment {
    class ClassDefinition {
    public:

        using Name = rasph::utils::NamedType<std::string, struct ClassName>;
        using Events = rasph::utils::NamedType<std::vector<std::string>, struct DefinedEvents>;
        using Attributes = rasph::utils::NamedType<std::vector<std::string>, struct DefinedAttributes>;

        ClassDefinition(Name name, Events events, Attributes attributes);

        const std::string &getName() const;

        virtual ~ClassDefinition() = default;

    private:
        const std::string name_;

    };
}


#endif //RASPH_CLASSDEFINITION_HPP
