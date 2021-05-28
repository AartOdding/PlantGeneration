#include "target.hpp"

Mb4::Targetable::Targetable(f32 sphere_radius, glm::fvec3 position, u32 identifier) :
	sphere_radius(sphere_radius),
	position(position),
	identifier(identifier)
{}