#pragma once

#include <cstdint>
#include <unordered_map>

#include <LSystem/Forward.hpp>
#include <LSystem/Plant.hpp>


class OperationDatabase
{
public:

	struct OperationIDs
	{
		const LSystem::Operation* operation;
		const std::uint64_t node_id;
		const std::uint64_t input_id;
		const std::uint64_t output_id;
	};

	struct ConnectionIDs
	{
		LSystem::Connection connection;
		const std::uint64_t connection_id;
	};

	void Update(LSystem::Plant* plant);

	OperationIDs Get(const LSystem::Operation* op) const;
	ConnectionIDs Get(const LSystem::Connection& con) const;

	OperationIDs FindOutputID(std::uint64_t output_id) const;
	OperationIDs FindInputID(std::uint64_t input_id) const;

	bool IsValidOutputID(std::uint64_t output_id) const;
	bool IsValidInputID(std::uint64_t input_id) const;

private:

	std::unordered_map<const LSystem::Operation*, OperationIDs> m_operations;
	std::unordered_map<LSystem::Connection, ConnectionIDs> m_connections;

};
