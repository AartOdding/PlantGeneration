#include <unordered_set>

#include <LSystem/LSystem.hpp>

#include "OperationDatabase.hpp"


static uint64_t unique_id = 123432;

void OperationDatabase::Update(LSystem::Plant* plant)
{
	std::unordered_set<LSystem::Operation*> operations{ plant->Operations().begin(), plant->Operations().end() };

	// Delete all operations that no longer exist:

	std::vector<LSystem::Operation*> to_delete;

	for (auto& [op, entry] : m_entries)
	{
		if (operations.count(op) == 0)
		{
			to_delete.push_back(op);
		}
	}

	for (auto op : to_delete)
	{
		m_entries.erase(op);
	}

	// Add new operations:

	for (auto op : operations)
	{
		if (m_entries.count(op) == 0)
		{
			m_entries.emplace(op, Entry{ op, ++unique_id, ++unique_id, ++unique_id });
		}
	}
}

OperationDatabase::Entry OperationDatabase::Get(LSystem::Operation* op) const
{
	if (m_entries.count(op))
	{
		return m_entries.at(op);
	}
	return {};
}
