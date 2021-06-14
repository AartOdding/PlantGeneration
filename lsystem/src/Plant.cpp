#include <algorithm>

#include <LSystem/Connection.hpp>
#include <LSystem/Plant.hpp>
#include <LSystem/Operations/StartOperation.hpp>
#include <LSystem/Utils/Serialization.hpp>

#include <LSystem/Operations/Registration.hpp>
#include <LSystem/Parameters/Registration.hpp>


CEREAL_CLASS_VERSION(LSystem::Connection, LSystem::Connection::Version);
CEREAL_CLASS_VERSION(LSystem::Operation, LSystem::Operation::Version);



namespace LSystem
{

	Plant::Plant()
	{
		AddOperation(std::make_unique<StartOperation>());
	}

	Operation* Plant::AddOperation(std::unique_ptr<Operation>&& operation)
	{
		m_operation_pointers.push_back(operation.get());
		m_operation_pointers_const.push_back(operation.get());
		m_operations_owned.push_back(std::move(operation));
		return m_operation_pointers.back();
	}

	bool Plant::DeleteOperation(Identifier<Operation> operation)
	{
		const auto size_begin = m_operations_owned.size();

		m_operation_pointers.erase(
			std::remove_if(
				m_operation_pointers.begin(),
				m_operation_pointers.end(),
				[operation](auto op) { return op->GetID() == operation; }),
			m_operation_pointers.end());

		m_operation_pointers_const.erase(
			std::remove_if(
				m_operation_pointers_const.begin(),
				m_operation_pointers_const.end(),
				[operation](auto op) { return op->GetID() == operation; }),
			m_operation_pointers_const.end());

		m_operations_owned.erase(
			std::remove_if(
				m_operations_owned.begin(), 
				m_operations_owned.end(), 
				[operation](const auto& op) { return op->GetID() == operation; }), 
			m_operations_owned.end());

		return m_operations_owned.size() < size_begin;
	}

	const std::vector<Operation*>& Plant::Operations()
	{
		return m_operation_pointers;
	}

	const std::vector<const Operation*>& Plant::Operations() const
	{
		return m_operation_pointers_const;
	}

	Operation* Plant::GetOperation(Identifier<Operation> operation)
	{
		for (auto op : m_operation_pointers)
		{
			if (op->GetID() == operation)
			{
				return op;
			}
		}
		return nullptr;
	}

	const Operation* Plant::GetOperation(Identifier<Operation> operation) const
	{
		for (auto op : m_operation_pointers_const)
		{
			if (op->GetID() == operation)
			{
				return op;
			}
		}
		return nullptr;
	}

	StartOperation* Plant::GetStartOperation()
	{
		for (auto op : m_operation_pointers)
		{
			if (dynamic_cast<StartOperation*>(op))
			{
				return static_cast<StartOperation*>(op);
			}
		}
		return nullptr;
	}

	const StartOperation* Plant::GetStartOperation() const
	{
		for (auto op : m_operation_pointers_const)
		{
			if (dynamic_cast<const StartOperation*>(op))
			{
				return static_cast<const StartOperation*>(op);
			}
		}
		return nullptr;
	}

	bool Plant::AddConnection(const Connection& connection)
	{
		if (m_connections.count(connection) == 0)
		{
			m_connections.emplace(connection);
			return true;
		}
		return false;
	}

	bool Plant::DeleteConnection(const Connection& connection)
	{
		if (m_connections.count(connection) > 0)
		{
			m_connections.erase(connection);
			return true;
		}
		return false;
	}

	const std::unordered_set<Connection>& Plant::Connections() const
	{
		return m_connections;
	}

	void Plant::Clear()
	{
		m_connections.clear();
		m_operations_owned.clear();
		m_operation_pointers.clear();
		m_operation_pointers_const.clear();
	}

	void Plant::SaveTo(std::ostream& output_stream) const
	{
		cereal::PortableBinaryOutputArchive archive(output_stream);
		archive(*this);
	}

	void Plant::LoadFrom(std::istream& input_stream)
	{
		Clear();
		cereal::PortableBinaryInputArchive archive(input_stream);
		archive(*this);
	}

	VertexBuffer Plant::Generate()
	{
		InstructionPool lsystem;

		auto start = GetStartOperation();

		if (start)
		{
			for (auto& op : m_operations_owned)
			{
				op->ResetState();
			}

			start->Execute(0, {}, lsystem, this);
		}

		return lsystem.Generate(1);
	}

	void Plant::ActivateOutput(Operation* output, int output_index, const std::vector<Instruction*>& output_values, InstructionPool& lsystem)
	{
		auto next = GetConnectedOperations(output, output_index);

		for (auto& [op, index] : next)
		{
			op->Execute(index, output_values, lsystem, this);
		}
	}


	std::vector<std::pair<Operation*, int>> Plant::GetConnectedOperations(Operation* output, int output_index)
	{
		std::vector<std::pair<Operation*, int>> connections;

		for (auto& c : m_connections)
		{
			if (c.output == output->GetID() && c.output_index == output_index)
			{
				connections.push_back({ GetOperation(c.input), c.input_index });
			}
		}

		return connections;
	}

}
