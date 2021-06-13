#pragma once

#include <LSystem/Utils/Serialization.hpp>

#include <LSystem/Operations/ColoringOperation.hpp>
#include <LSystem/Operations/ExtrudeOperation.hpp>
#include <LSystem/Operations/FanOperation.hpp>
#include <LSystem/Operations/ForkOperation.hpp>
#include <LSystem/Operations/LoopOperation.hpp>
#include <LSystem/Operations/PhyllotaxisOperation.hpp>
#include <LSystem/Operations/RadiusOperation.hpp>
#include <LSystem/Operations/RandomColorOperation.hpp>
#include <LSystem/Operations/RandomLengthOperation.hpp>
#include <LSystem/Operations/ScaleOperation.hpp>
#include <LSystem/Operations/StartOperation.hpp>



CEREAL_REGISTER_TYPE(LSystem::ColoringOperation)
CEREAL_REGISTER_TYPE(LSystem::ExtrudeOperation)
CEREAL_REGISTER_TYPE(LSystem::FanOperation)
CEREAL_REGISTER_TYPE(LSystem::ForkOperation)
CEREAL_REGISTER_TYPE(LSystem::LoopOperation)
CEREAL_REGISTER_TYPE(LSystem::PhyllotaxisOperation)
CEREAL_REGISTER_TYPE(LSystem::RadiusOperation)
CEREAL_REGISTER_TYPE(LSystem::RandomColorOperation)
CEREAL_REGISTER_TYPE(LSystem::RandomLengthOperation)
CEREAL_REGISTER_TYPE(LSystem::ScaleOperation)
CEREAL_REGISTER_TYPE(LSystem::StartOperation)
