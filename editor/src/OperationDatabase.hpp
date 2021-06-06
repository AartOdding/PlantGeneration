#pragma once

#include <cstdint>
#include <unordered_map>

#include <LSystem/Forward.hpp>



class OperationDatabase
{
public:

	struct Entry
	{
		const LSystem::Operation* operation;
		const std::uint64_t node_id;
		const std::uint64_t input_id;
		const std::uint64_t output_id;
	};

	void Update(LSystem::Plant* plant);

	Entry Get(LSystem::Operation* op) const;

private:

	std::unordered_map<LSystem::Operation*, Entry> m_entries;

};
