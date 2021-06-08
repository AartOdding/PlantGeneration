#include <algorithm>
#include <cassert>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	Operation::Operation(Plant* plant)
		: m_plant(plant)
	{
		assert(m_plant);

		if (m_plant)
		{
			m_plant->m_operations.push_back(this);
		}
	}

	Operation::~Operation()
	{
		if (m_plant)
		{
			m_plant->m_operations.erase(
				std::remove(
					m_plant->m_operations.begin(),
					m_plant->m_operations.end(), this),
				m_plant->m_operations.end());
		}
	}

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, LSystem& lsystem)
	{
		m_plant->ActivateOutput(this, output_index, output_values, lsystem);
	}

}
