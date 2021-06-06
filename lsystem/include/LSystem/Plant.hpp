#pragma once

#include <memory>
#include <string_view>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/OperationOwner.hpp>



namespace LSystem
{

	struct Connection
	{
		Operation* output;
		Operation* input;
	};

	struct Plant : OperationOwner
	{
		void CreateConnection(Operation* output, Operation* input);

		ColoringOperation* CreateColoringOperation(std::string_view name);
		ExtrudeOperation* CreateExtrudeOperation(std::string_view name);
		FanOperation* CreateFanOperation(std::string_view name);
		PhyllotaxisOperation* CreatePhyllotaxisOperation(std::string_view name);
		ForkOperation* CreateForkOperation(std::string_view name);

	private:

		std::vector<Connection> m_connections;
		std::vector<std::unique_ptr<Operation>> m_operationsOwned;

	};

}
