#include <LSystem/ParameterOwner.hpp>

using namespace LSystem;


const std::vector<Parameter*>& ParameterOwner::Parameters()
{
	return m_parameters;
}
