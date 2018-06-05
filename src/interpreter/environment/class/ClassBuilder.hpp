//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_CLASSBUILDER_HPP
#define RASPH_CLASSBUILDER_HPP

#include <unordered_map>
#include <functional>
#include "ClassDefinition.hpp"

namespace rasph::common::ast::nodes {
    class ClassNode;

    class AttributeMemberNode;

    class EventMemberNode;

    class MethodMemberNode;
}

namespace rasph::interpreter::environment {
    class ClassBuilder {
    public:

        void build(common::ast::nodes::ClassNode const &);

        void addElement(common::ast::nodes::AttributeMemberNode const &);

        void addElement(common::ast::nodes::EventMemberNode const &);

        void addElement(common::ast::nodes::MethodMemberNode const &);

        virtual ~ClassBuilder() = default;

    private:

        void compose();

        std::string name_;
        std::vector<std::string> attributes_;
        std::vector<std::string> events_;
        std::vector<std::pair<std::string, rasph::common::ast::nodes::MethodMemberNode*>> methods_;

    };
}


#endif //RASPH_CLASSBUILDER_HPP
