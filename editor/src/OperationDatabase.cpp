#include <unordered_set>

#include <LSystem/LSystem.hpp>

#include "OperationDatabase.hpp"


static uint64_t unique_id = 123432;

void OperationDatabase::Update(LSystem::Plant* plant)
{
	/////////   Operations:      ///////////////

	std::unordered_set<const LSystem::Operation*> operations{ plant->Operations().begin(), plant->Operations().end() };

	// Delete all operations that no longer exist:

	std::vector<const LSystem::Operation*> operations_to_delete;

	for (auto& [op, ids] : m_operations)
	{
		if (operations.count(op) == 0)
		{
			operations_to_delete.push_back(op);
		}
	}

	for (auto op : operations_to_delete)
	{
		m_operations.erase(op);
	}

	// Add new operations:

	for (auto op : operations)
	{
		if (m_operations.count(op) == 0)
		{
			m_operations.emplace(op, OperationIDs{ op, ++unique_id, ++unique_id, ++unique_id });
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

OperationDatabase::OperationIDs OperationDatabase::Get(const LSystem::Operation* op) const
{
	if (m_operations.count(op))
	{
		return m_operations.at(op);
	}
	return {};
}

OperationDatabase::ConnectionIDs OperationDatabase::Get(const LSystem::Connection& con) const
{
	if (m_connections.count(con))
	{
		return m_connections.at(con);
	}
	return {};
}

OperationDatabase::OperationIDs OperationDatabase::FindOutputID(std::uint64_t output_id) const
{
	for (auto& [op, ids] : m_operations)
	{
		if (ids.output_id == output_id)
		{
			return ids;
		}
	}
	return {};
}

OperationDatabase::OperationIDs OperationDatabase::FindInputID(std::uint64_t input_id) const
{
	for (auto& [op, ids] : m_operations)
	{
		if (ids.input_id == input_id)
		{
			return ids;
		}
	}
	return {};
}

bool OperationDatabase::IsValidOutputID(std::uint64_t output_id) const
{
	for (auto& [op, ids] : m_operations)
	{
		if (ids.output_id == output_id)
		{
			return true;
		}
	}
	return false;
}

bool OperationDatabase::IsValidInputID(std::uint64_t input_id) const
{
	for (auto& [op, ids] : m_operations)
	{
		if (ids.input_id == input_id)
		{
			return true;
		}
	}
	return false;
}
