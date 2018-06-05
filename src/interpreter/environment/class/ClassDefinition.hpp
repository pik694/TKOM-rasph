//
// Created by Piotr Żelazko on 04.06.2018.
//

#ifndef RASPH_CLASSDEFINITION_HPP
#define RASPH_CLASSDEFINITION_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <utils/NamedType.hpp>
#include <common/types/Object.hpp>

namespace rasph::common::ast::nodes {
    class MethodMemberNode;
}


namespace rasph::interpreter::environment {
    class ClassDefinition : public common::types::Object{
    public:

        using Name = rasph::utils::NamedType<std::string, struct ClassName>;
        using Events = rasph::utils::NamedType<std::vector<std::string>, struct DefinedEvents>;
        using Attributes = rasph::utils::NamedType<std::vector<std::string>, struct DefinedAttributes>;
        using Methods = rasph::utils::NamedType<std::unordered_map<std::string, rasph::common::ast::nodes::MethodMemberNode *>, struct DefinedMethods>;

        ClassDefinition(Name name, Events events, Attributes attributes, Methods methods);

        rasph::common::ast::nodes::MethodMemberNode* getMethod(const std::string&) const;


        const std::string &getName() const;

        virtual ~ClassDefinition() = default;

    private:

        explicit operator bool() const override;

        bool operator!() const override;

        bool operator==(Object const &object) const override;

        bool operator<(Object const &object) const override;

        bool operator>(Object const &object) const override;

        std::unique_ptr<Object> accept(const common::types::visitors::AddVisitor &visitor) const override;

        std::unique_ptr<Object> accept(const common::types::visitors::SubtractVisitor &visitor) const override;

        std::unique_ptr<Object> accept(const common::types::visitors::MultiplyVisitor &visitor) const override;

        std::unique_ptr<Object> accept(const common::types::visitors::DivideVisitor &visitor) const override;

        ClassDefinition *copyImplementation() const override;


    private:
        const std::string name_;
        const std::vector<std::string> attributes_;
        const std::vector<std::string> events_;
        const std::unordered_map<std::string, rasph::common::ast::nodes::MethodMemberNode* > methods_;


    };
}


#endif //RASPH_CLASSDEFINITION_HPP
