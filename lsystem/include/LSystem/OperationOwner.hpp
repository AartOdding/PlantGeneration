#pragma once

#include <vector>



namespace LSystem
{

    struct Operation;

    struct OperationOwner
    {
        virtual ~OperationOwner() = default;

        const std::vector<Operation*>& Operations();

    private:

        friend class Operation;

        std::vector<Operation*> m_operations;

    };

}
