#pragma once

#include <vector>

#include <LSystem/Forward.hpp>



namespace LSystem
{

    struct ParameterOwner
    {
        virtual ~ParameterOwner() = default;

        bool AddParameter(Parameter& parameter);
        bool RemoveParameter(Parameter& parameter);

        const std::vector<Parameter*>& Parameters();
        const std::vector<const Parameter*>& Parameters() const;

    private:

        std::vector<Parameter*> m_parameters;
        std::vector<const Parameter*> m_const_parameters;

    };

}
