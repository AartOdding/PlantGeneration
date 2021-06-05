#include <LSystem/ParameterOwner.hpp>

using namespace LSystem;


const std::vector<IParameter*>& ParameterOwner::Parameters()
{
	return m_parameters;
}
