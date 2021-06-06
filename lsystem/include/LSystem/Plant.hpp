#pragma once

#include <memory>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/OperationOwner.hpp>



namespace LSystem
{

	struct Connection
	{
		const Operation* output;
		const Operation* input;

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
			auto h1 = std::hash<const LSystem::Operation*>()(c.output);
			auto h2 = std::hash<const LSystem::Operation*>()(c.input);
			return h1 ^ (h2 << 1);
		}
	};
}


namespace LSystem
{

	struct Plant : OperationOwner
	{
		ColoringOperation* CreateColoringOperation(std::string_view name);
		ExtrudeOperation* CreateExtrudeOperation(std::string_view name);
		FanOperation* CreateFanOperation(std::string_view name);
		PhyllotaxisOperation* CreatePhyllotaxisOperation(std::string_view name);
		ForkOperation* CreateForkOperation(std::string_view name);

		bool CreateConnection(const Operation* output, const Operation* input);
		bool AreConnected(const Operation* output, const Operation* input) const;
		const std::unordered_set<Connection>& Connections() const;

	private:

		std::unordered_set<Connection> m_connections;
		std::vector<std::unique_ptr<Operation>> m_operationsOwned;

	};

}
