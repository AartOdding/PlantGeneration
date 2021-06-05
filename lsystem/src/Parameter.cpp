#include <cassert>

#include <LSystem/LSystem.hpp>

using namespace LSystem;


IParameter::IParameter(ParameterOwner* _owner, std::string_view _name)
	: owner(_owner)
	, name(_name)
{
	assert(owner);

	if (owner)
	{
		owner->m_parameters.push_back(this);
	}
}

IParameter::~IParameter()
{
	if (owner)
	{
		owner->m_parameters.erase(
			std::remove(
				owner->m_parameters.begin(),
				owner->m_parameters.end(), this),
			owner->m_parameters.end());
	}
}

FloatParameter::FloatParameter(ParameterOwner* owner, std::string_view name, float _min, float _max, float _value)
	: IParameter(owner, name)
	, min(_min)
	, max(_max)
	, value(_value)
{

}

IntParameter::IntParameter(ParameterOwner* owner, std::string_view name, int _min, int _max, int _value)
	: IParameter(owner, name)
	, min(_min)
	, max(_max)
	, value(_value)
{

}

ColorParameter::ColorParameter(ParameterOwner* owner, std::string_view name, glm::vec3 _value)
	: IParameter(owner, name)
	, value(_value)
{

}
