#include <algorithm>

#include "Tree.hpp"



const std::vector<Tree::IParameter*>& Tree::Parameters()
{
	return m_parameters;
}


Tree::IParameter::IParameter(Tree* _tree, std::string_view _name)
	: tree(_tree)
	, name(_name)
{
	assert(tree);

	if (tree)
	{
		tree->m_parameters.push_back(this);
	}
}

Tree::IParameter::~IParameter()
{
	if (tree)
	{
		tree->m_parameters.erase(
			std::remove(
				tree->m_parameters.begin(),
				tree->m_parameters.end(), this),
			tree->m_parameters.end());
	}
}

Tree::Float::Float(Tree* tree, std::string_view name, float _min, float _max, float _value)
	: Tree::IParameter(tree, name)
	, min(_min)
	, max(_max)
	, value(_value)
{

}

Tree::Int::Int(Tree* tree, std::string_view name, int _min, int _max, int _value)
	: Tree::IParameter(tree, name)
	, min(_min)
	, max(_max)
	, value(_value)
{

}


Tree::Color::Color(Tree* tree, std::string_view name, glm::vec3 _value)
	: Tree::IParameter(tree, name)
	, value(_value)
{

}
