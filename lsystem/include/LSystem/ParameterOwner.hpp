#pragma once

#include <vector>



namespace LSystem
{

    struct Parameter;

    struct ParameterOwner
    {
        virtual ~ParameterOwner() = default;

        const std::vector<Parameter*>& Parameters();

    private:

        friend class Parameter;

        std::vector<Parameter*> m_parameters;

    };

}
