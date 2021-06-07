#pragma once

#include <memory>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/OperationOwner.hpp>
#include <LSystem/VertexBuffer.hpp>



namespace LSystem
{

	struct Connection
	{
		Operation* const output;
		Operation* const input;

		bool operator==(const Connection& other) const
		{
			return output == other.output && input == other.input;
		}
	};

}


namespace std
{
	template <>
	struct hash<LSystem::Connection>
	{
		std::size_t operator()(const LSystem::Connection& c) const
		{
			auto h1 = std::hash<LSystem::Operation*>()(c.output);
			auto h2 = std::hash<LSystem::Operation*>()(c.input);
			return h1 ^ (h2 << 1);
		}
	};
}


namespace LSystem
{

	struct Plant : OperationOwner
	{
		Plant();

		ColoringOperation* CreateColoringOperation(std::string_view name);
		ExtrudeOperation* CreateExtrudeOperation(std::string_view name);
		FanOperation* CreateFanOperation(std::string_view name);
		PhyllotaxisOperation* CreatePhyllotaxisOperation(std::string_view name);
		ForkOperation* CreateForkOperation(std::string_view name);
		RandomColorOperation* CreateRandomColorOperation(std::string_view name);
		RandomLengthOperation* CreateRandomLengthOperation(std::string_view name);

		bool DeleteOperation(Operation* operation);

		bool CreateConnection(Operation* output, Operation* input);
		bool DeleteConnection(Operation* output, Operation* input);
		bool AreConnected(Operation* output, Operation* input) const;
		const std::unordered_set<Connection>& Connections() const;

		VertexBuffer Generate();

	private:

		std::vector<Instruction*> ExecuteOperation(Operation* operation, const std::vector<Instruction*>& instructions, LSystem& lsystem);
		std::vector<Operation*> GetNextOperations(Operation* operation);

		std::unordered_set<Connection> m_connections;
		std::vector<std::unique_ptr<Operation>> m_operations_owned;
		Operation* m_start_operation;

	};

}
