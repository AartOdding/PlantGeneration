#include <LSystem/ParameterList.hpp>



namespace LSystem
{

	bool ParameterList::AddParameter(Parameter& parameter)
	{
		auto par = std::find(m_parameters.begin(), m_parameters.end(), &parameter);

		if (par == m_parameters.end())
		{
			m_parameters.push_back(&parameter);
			m_const_parameters.push_back(&parameter);
			return true;
		}
		return false;
	}

	bool ParameterList::RemoveParameter(Parameter& parameter)
	{
		auto par = std::find(m_parameters.begin(), m_parameters.end(), &parameter);
		auto par_const = std::find(m_const_parameters.begin(), m_const_parameters.end(), &parameter);

		if (par != m_parameters.end())
		{
			m_parameters.erase(par);
			m_const_parameters.erase(par_const);
			return true;
		}
		return false;
	}

	const std::vector<Parameter*>& ParameterList::Parameters()
	{
		return m_parameters;
	}

	const std::vector<const Parameter*>& ParameterList::Parameters() const
	{
		return m_const_parameters;
	}

}
