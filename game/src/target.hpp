#pragma once

#include <raymath.h>
#include "types.hpp"
#include <iterator>
#include <glm/glm.hpp>
#include <optional>
#include <tuple>

namespace Mb4
{

struct Targetable
{
public:
	f32 sphere_radius;
	glm::fvec3 position;
	u32 identifier;

	Targetable(f32 sphere_radius, glm::fvec3 position, u32 identifier);
};

/* Find the targeted object.
 * 
 * first, last iterators to collection of pointers to const Targetables.
 * @return identifier of targeted object, if any. */
template<typename ConstForwardIterator>
std::optional<u32> GetTarget(ConstForwardIterator first, ConstForwardIterator last, Vector3 camera_position, Vector3 camera_forward)
{
	// stores closest (identifier, collision_point)
	std::optional<std::tuple<u32, Vector3>> closest;

	for (; first != last; ++first)
	{
		Ray ray;
		ray.direction = Vector3Normalize(Vector3Subtract(camera_forward, camera_position));
		ray.position = camera_position;

		Vector3 raylib_position;
		raylib_position.x = (*first)->position.x;
		raylib_position.y = (*first)->position.y;
		raylib_position.z = (*first)->position.z;

		Vector3 sphere_collision;
		bool targeting_sphere = CheckCollisionRaySphereEx(ray, raylib_position, (*first)->sphere_radius, &sphere_collision);
		if (targeting_sphere)
		{
			if (
				!closest.has_value() ||
				Vector3LengthSqr(Vector3Subtract(sphere_collision, camera_position)) < Vector3LengthSqr(Vector3Subtract(std::get<1>(closest.value()), camera_position))
			)
			{
				closest = std::make_tuple((*first)->identifier, sphere_collision);
			}
		}
	}

	if (closest.has_value())
	{
		return { std::get<0>(closest.value()) };
	}

	return {};
}

}