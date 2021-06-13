#include <unordered_set>

#include <LSystem/LSystem.hpp>

#include "OperationDatabase.hpp"


static uint64_t unique_id = 123432;

void OperationDatabase::Update(LSystem::Plant* plant)
{
	/////////   Operations:      ///////////////

	std::unordered_set<LSystem::Identifier<LSystem::Operation>> operations;
	operations.reserve(plant->Operations().size());

	for (auto op : plant->Operations())
	{
		operations.insert(op->GetID());
	}

	// Delete all operations that no longer exist:

	std::vector<LSystem::Identifier<LSystem::Operation>> operations_to_delete;

	for (auto& [op, ids] : m_operations)
	{
		if (operations.count(ids.operation) == 0)
		{
			operations_to_delete.push_back(op);
		}
	}

	for (auto op : operations_to_delete)
	{
		m_operations.erase(op);
	}

	// Add new operations:

	for (auto op : plant->Operations())
	{
		if (m_operations.count(op->GetID()) == 0)
		{
			std::uint64_t operation_id = ++unique_id;
			std::vector<std::uint64_t> input_ids;
			for (int i = 0; i < op->GetInfo().input_count; ++i) input_ids.push_back(++unique_id);
			std::vector<std::uint64_t> output_ids;
			for (int i = 0; i < op->GetInfo().output_count; ++i) output_ids.push_back(++unique_id);

			m_operations.emplace(op->GetID(), OperationIDs{ op->GetID(), operation_id, input_ids, output_ids });
		}
	}

	/////////   Connections:      ///////////////

	std::unordered_set<LSystem::Connection> connections{ plant->Connections().begin(), plant->Connections().end() };

	// Delete all connections that no longer exist:

	std::vector<LSystem::Connection> connections_to_delete;

	for (auto& [con, ids] : m_connections)
	{
		if (connections.count(con) == 0)
		{
			connections_to_delete.push_back(con);
		}
	}

	for (auto con : connections_to_delete)
	{
		m_connections.erase(con);
	}

	// Add new connections:

	for (auto con : connections)
	{
		if (m_connections.count(con) == 0)
		{
			m_connections.emplace(con, ConnectionIDs{ con, ++unique_id });
		}
	}
}

std::uint64_t OperationDatabase::GetOperationID(LSystem::Identifier<LSystem::Operation> op) const
{
	if (m_operations.count(op))
	{
		return m_operations.at(op).operation_id;
	}
	return 0;
}

std::uint64_t OperationDatabase::GetInputID(LSystem::Identifier<LSystem::Operation> op, int index) const
{
	if (m_operations.count(op))
	{
		if (index >= 0 && index < m_operations.at(op).input_ids.size())
		{
			return m_operations.at(op).input_ids[index];
		}
	}
	return 0;
}

std::uint64_t OperationDatabase::GetOutputID(LSystem::Identifier<LSystem::Operation> op, int index) const
{
	if (m_operations.count(op))
	{
		if (index >= 0 && index < m_operations.at(op).output_ids.size())
		{
			return m_operations.at(op).output_ids[index];
		}
	}
	return 0;
}

std::uint64_t OperationDatabase::GetConnectionID(const LSystem::Connection& con) const
{
	if (m_connections.count(con))
	{
		return m_connections.at(con).connection_id;
	}
	return 0;
}

LSystem::Identifier<LSystem::Operation> OperationDatabase::GetOperation(std::uint64_t id) const
{
	for (auto& [op, ids] : m_operations)
	{
		if (ids.operation_id == id)
		{
			return op;
		}
	}
	return {};
}

std::pair<LSystem::Identifier<LSystem::Operation>, int> OperationDatabase::GetInput(std::uint64_t id) const
{
	for (auto& [op, ids] : m_operations)
	{
		for (int i = 0; i < ids.input_ids.size(); ++i)
		{
			if (ids.input_ids[i] == id)
			{
				return { op, i };
			}
		}
	}
	return { {}, -1 };
}

std::pair<LSystem::Identifier<LSystem::Operation>, int> OperationDatabase::GetOutput(std::uint64_t id) const
{
	for (auto& [op, ids] : m_operations)
	{
		for (int i = 0; i < ids.output_ids.size(); ++i)
		{
			if (ids.output_ids[i] == id)
			{
				return { op, i };
			}
		}
	}
	return { {}, -1 };
}

LSystem::Connection OperationDatabase::GetConnection(std::uint64_t id) const
{
	for (auto& [con, ids] : m_connections)
	{
		if (ids.connection_id == id)
		{
			return con;
		}
	}
	return LSystem::Connection();
}


bool OperationDatabase::IsOperationID(std::uint64_t id) const
{
	return GetOperation(id) != LSystem::Identifier<LSystem::Operation>();
}

bool OperationDatabase::IsInputID(std::uint64_t id) const
{
	return GetInput(id) != std::pair{ LSystem::Identifier<LSystem::Operation>(), -1 };
}

bool OperationDatabase::IsOutputID(std::uint64_t id) const
{
	return GetOutput(id) != std::pair{ LSystem::Identifier<LSystem::Operation>(), -1 };
}

bool OperationDatabase::IsConnectionID(std::uint64_t id) const
{
	return GetConnection(id) != LSystem::Connection{};
}
