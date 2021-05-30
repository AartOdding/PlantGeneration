#pragma once

#include <glm/glm.hpp>

#include "types.hpp"
#include "sphere_world.hpp"

namespace Mb4
{

class Player
{
public:
	glm::fvec3 position;
	glm::fvec3 velocity;

	glm::fvec3 forward;

	Player(glm::fvec3 position, glm::fvec3 forward);
	void Update(f32 deltatime, f32 gravityStrenght, SphereWorld const& world);

};

}