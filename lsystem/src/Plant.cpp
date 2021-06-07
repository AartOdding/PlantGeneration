#include <algorithm>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	Plant::Plant()
	{
		m_operations_owned.push_back(std::make_unique<StartOperation>(this, "Start"));
		m_start_operation = m_operations_owned.back().get();
	}

	ColoringOperation* Plant::CreateColoringOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<ColoringOperation>(this, name));
		return static_cast<ColoringOperation*>(m_operations_owned.back().get());
	}

	ExtrudeOperation* Plant::CreateExtrudeOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<ExtrudeOperation>(this, name));
		return static_cast<ExtrudeOperation*>(m_operations_owned.back().get());
	}

	FanOperation* Plant::CreateFanOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<FanOperation>(this, name));
		return static_cast<FanOperation*>(m_operations_owned.back().get());
	}

	PhyllotaxisOperation* Plant::CreatePhyllotaxisOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<PhyllotaxisOperation>(this, name));
		return static_cast<PhyllotaxisOperation*>(m_operations_owned.back().get());
	}

	ForkOperation* Plant::CreateForkOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<ForkOperation>(this, name));
		return static_cast<ForkOperation*>(m_operations_owned.back().get());
	}

	RandomLengthOperation* Plant::CreateRandomLengthOperation(std::string_view name)
	{
		m_operations_owned.push_back(std::make_unique<RandomLengthOperation>(this, name));
		return static_cast<RandomLengthOperation*>(m_operations_owned.back().get());
	}

	bool Plant::DeleteOperation(Operation* operation)
	{
		const auto size_begin = m_operations_owned.size();

		m_operations_owned.erase(
			std::remove_if(
				m_operations_owned.begin(), 
				m_operations_owned.end(), 
				[operation](const auto& op) { return op.get() == operation; }), 
			m_operations_owned.end());

		return m_operations_owned.size() < size_begin;
	}

	bool Plant::CreateConnection(Operation* output, Operation* input)
	{
		if (m_connections.count(Connection{ output, input }) == 0)
		{
			m_connections.emplace(Connection{ output, input });
			return true;
		}
		return false;
	}

	bool Plant::DeleteConnection(Operation* output, Operation* input)
	{
		if (m_connections.count(Connection{ output, input }) > 0)
		{
			m_connections.erase(Connection{ output, input });
			return true;
		}
		return false;
	}

	bool Plant::AreConnected(Operation* output, Operation* input) const
	{
		return m_connections.count(Connection{ output, input });
	}

	const std::unordered_set<Connection>& Plant::Connections() const
	{
		return m_connections;
	}

	std::vector<Instruction*> Plant::ExecuteOperation(Operation* operation, const std::vector<Instruction*>& instructions, LSystem& lsystem)
	{
		auto new_instructions = operation->Apply(instructions, lsystem);
		auto next_ops = GetNextOperations(operation);

		for (auto op : next_ops)
		{
			ExecuteOperation(op, new_instructions, lsystem);
		}

		return new_instructions;
	}

	VertexBuffer Plant::Generate()
	{
		LSystem lsystem;

		auto start = ExecuteOperation(m_start_operation, {}, lsystem);

		return ::LSystem::Generate(start[0], 1);
	}


	std::vector<Operation*> Plant::GetNextOperations(Operation* operation)
	{
		std::vector<Operation*> next_operations;

		for (auto& c : m_connections)
		{
			if (c.output == operation)
			{
				next_operations.push_back(c.input);
			}
		}

		return next_operations;
	}
}
