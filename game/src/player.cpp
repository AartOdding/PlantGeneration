#include "player.hpp"
#include "debug.hpp"
#include <string>
#include <cmath>
#include <glm/gtc/noise.hpp>
#include <raylib.h>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <algorithm>

using namespace Mb4;

Player::Player(glm::fvec3 position, glm::fvec3 forward) :
	position(position),
	velocity({0.0_f32, 0.0_f32, 0.0_f32}),
	forward(forward)
{}

void Player::Update(f32 deltatime, f32 gravity_strenght, SphereWorld const& world, glm::fvec2 mouse_movement)
{
	constexpr f32 mouse_speed = 0.5_f32;

	// mouse y to move camera up and down
	updownangle -= mouse_movement.y * mouse_speed * deltatime;
	updownangle = std::clamp(updownangle, -0.5_f32 * PI + 0.1_f32, 0.5_f32 * PI - 0.1_f32);

	// mouse x to rotate
	forward = glm::angleAxis(-mouse_movement.x * mouse_speed * deltatime, glm::normalize(position)) * forward;

	// apply movement acceleration
	f32 current_height = world.GetHeight(position);
	glm::fvec3 acceleration = {0.0_f32, 0.0_f32, 0.0_f32};
	if (IsKeyDown(KEY_W) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		acceleration += forward;
	}
	if (IsKeyDown(KEY_S) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		acceleration -= forward;
	}
	if (IsKeyDown(KEY_D) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		acceleration += glm::cross(forward, glm::normalize(position));
	}
	if (IsKeyDown(KEY_A) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		acceleration -= glm::cross(forward, glm::normalize(position));
	}
	if (glm::length(acceleration) > 0.001)
	{
		acceleration = glm::normalize(acceleration) * deltatime * 15.0f;
		velocity += acceleration;
	}

	// add gravity
	velocity += gravity_strenght * -glm::normalize(position) * deltatime;

	// air drag
	velocity *= 0.99;

	// apply velocity
	glm::fvec3 new_position = position + velocity * deltatime;

	// if collision
	f32 height = world.GetHeight(new_position);
	glm::fvec3 heightvec = height * glm::normalize(new_position);
	if (glm::length(new_position) < height)
	{
		// handle collision physics
		new_position = heightvec;
		glm::fvec3 normal = world.GetNormal(new_position);
		velocity -= normal * glm::dot(velocity, normal);
		velocity *= 0.80;
	}

	glm::fvec3 axisangle = glm::cross(glm::normalize(position), glm::normalize(new_position));
	glm::fvec3 new_forward;
	if (glm::length(axisangle) != 0)
	{
		new_forward = glm::angleAxis(glm::length(axisangle), glm::normalize(axisangle)) * forward;
	}
	else
	{
		new_forward = forward;
	}
	
	// snap new_forward to nearest orthogonal verctor with up vector
	new_forward = glm::cross(glm::cross(glm::normalize(new_position), new_forward), glm::normalize(new_position));

	position = new_position;
	forward = new_forward;
}

glm::fvec3 Player::GetRotatedForward()
{
	auto rotation = glm::angleAxis(updownangle, glm::cross(forward, glm::normalize(position)));
	return rotation * forward;
}

glm::fvec3 Player::GetRotatedUp()
{
	auto rotation = glm::angleAxis(updownangle, glm::cross(forward, glm::normalize(position)));
	return rotation * glm::normalize(position);
}