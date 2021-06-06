#pragma once

#include <vector>

#include <LSystem/Forward.hpp>



namespace LSystem
{

    struct ParameterOwner
    {
        virtual ~ParameterOwner() = default;

        const std::vector<Parameter*>& Parameters();

    private:

        friend class Parameter;

        std::vector<Parameter*> m_parameters;

    };

}
