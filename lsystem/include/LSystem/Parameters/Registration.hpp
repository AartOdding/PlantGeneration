#pragma once

#include <LSystem/Utils/Serialization.hpp>

#include <LSystem/Parameters/BoolParameter.hpp>
#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>



CEREAL_REGISTER_TYPE(LSystem::BoolParameter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LSystem::Parameter, LSystem::BoolParameter)

CEREAL_REGISTER_TYPE(LSystem::ColorParameter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LSystem::Parameter, LSystem::ColorParameter)

CEREAL_REGISTER_TYPE(LSystem::FloatParameter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LSystem::Parameter, LSystem::FloatParameter)

CEREAL_REGISTER_TYPE(LSystem::IntParameter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LSystem::Parameter, LSystem::IntParameter)
