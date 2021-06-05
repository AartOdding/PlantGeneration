#pragma once

#include <vector>


namespace LSystem
{
    struct IParameter;

    struct ParameterOwner
    {
        virtual ~ParameterOwner() = default;

        const std::vector<IParameter*>& Parameters();

    private:

        friend class IParameter;

        std::vector<IParameter*> m_parameters;

    };
}
