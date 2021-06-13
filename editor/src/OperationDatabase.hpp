#pragma once

#include <cstdint>
#include <unordered_map>

#include <LSystem/Forward.hpp>
#include <LSystem/Plant.hpp>


class OperationDatabase
{
public:

	void Update(LSystem::Plant* plant);
	
	std::uint64_t GetOperationID(LSystem::Identifier<LSystem::Operation> op) const;
	std::uint64_t GetInputID(LSystem::Identifier<LSystem::Operation> op, int index) const;
	std::uint64_t GetOutputID(LSystem::Identifier<LSystem::Operation> op, int index) const;
	std::uint64_t GetConnectionID(const LSystem::Connection& con) const;

	LSystem::Identifier<LSystem::Operation> GetOperation(std::uint64_t id) const;
	std::pair<LSystem::Identifier<LSystem::Operation>, int> GetInput(std::uint64_t id) const;
	std::pair<LSystem::Identifier<LSystem::Operation>, int> GetOutput(std::uint64_t id) const;
	LSystem::Connection GetConnection(std::uint64_t id) const;

	bool IsOperationID(std::uint64_t id) const;
	bool IsInputID(std::uint64_t id) const;
	bool IsOutputID(std::uint64_t id) const;
	bool IsConnectionID(std::uint64_t id) const;

private:

	struct OperationIDs
	{
		const LSystem::Identifier<LSystem::Operation> operation;
		const std::uint64_t operation_id;
		const std::vector<std::uint64_t> input_ids;
		const std::vector<std::uint64_t> output_ids;
	};

	struct ConnectionIDs
	{
		LSystem::Connection connection;
		const std::uint64_t connection_id;
	};

	std::unordered_map<LSystem::Identifier<LSystem::Operation>, OperationIDs> m_operations;
	std::unordered_map<LSystem::Connection, ConnectionIDs> m_connections;

};
