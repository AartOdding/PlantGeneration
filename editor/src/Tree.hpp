#pragma once

#include <cassert>
#include <string>
#include <string_view>

#include <LSystem/LSystem.hpp>



struct Tree
{
	struct IParameter
	{
		IParameter(Tree* tree, std::string_view name);

		virtual ~IParameter();

		IParameter() = delete;
		IParameter(const IParameter&) = delete;
		IParameter(IParameter&) = delete;
		IParameter& operator=(const IParameter&) = delete;
		IParameter& operator=(IParameter&&) = delete;

		const std::string name;

	private:
		Tree* tree;
	};

	struct Float : IParameter
	{
		Float(Tree* tree, std::string_view name, float min, float max, float value);

		float min;
		float max;
		float value;

		operator float() const { return value; }
	};

	struct Int : IParameter
	{
		Int(Tree* tree, std::string_view name, int min, int max, int value);

		int min;
		int max;
		int value;

		operator int() const { return value; }
	};

	virtual ~Tree() = default;

	virtual LSystem::LSystem Generate() = 0;

	const std::vector<IParameter*>& Parameters();

private:

	friend class IParameter;

	std::vector<IParameter*> m_parameters;

};

