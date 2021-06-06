#pragma once

#include <vector>

#include <LSystem/Forward.hpp>



namespace LSystem
{

    struct OperationOwner
    {
        virtual ~OperationOwner() = default;

        const std::vector<Operation*>& Operations();

    private:

        friend class Operation;

        std::vector<Operation*> m_operations;

    };

}
