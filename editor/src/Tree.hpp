#pragma once

#include <cassert>
#include <string>
#include <string_view>

#include <LSystem/LSystem.hpp>



struct Tree : LSystem::ParameterOwner
	        , LSystem::OperationOwner
{

	using Int = LSystem::IntParameter;
	using Float = LSystem::FloatParameter;
	using Color = LSystem::ColorParameter;

	virtual ~Tree() = default;

	virtual LSystem::LSystem Generate() = 0;

};

