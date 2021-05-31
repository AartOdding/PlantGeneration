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
	f32 updownangle = 0.0_f32;

	Player(glm::fvec3 position, glm::fvec3 forward);
	void Update(f32 deltatime, f32 gravity_strenght, SphereWorld const& world, glm::fvec2 mouse_movement);
	
	glm::fvec3 GetRotatedForward();
	glm::fvec3 GetRotatedUp();
};

}