#include "player.hpp"
#include "debug.hpp"
#include <string>
#include <cmath>
#include <glm/gtc/noise.hpp>
#include <raylib.h>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

using namespace Mb4;

Player::Player(glm::fvec3 position, glm::fvec3 forward) :
	position(position),
	velocity({0.0_f32, 0.0_f32, 0.0_f32}),
	forward(forward)
{}

void Player::Update(f32 deltatime, f32 gravityStrength, SphereWorld const& world)
{
	f32 current_height = world.GetHeight(position);
	if (IsKeyDown(KEY_UP) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		velocity += forward * deltatime * 15.0f;
	}

	if (IsKeyDown(KEY_DOWN) && glm::distance(current_height, glm::length(position)) < 0.001)
	{
		velocity -= forward * deltatime * 15.0f;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		forward = glm::angleAxis(deltatime * 1.0_f32, glm::normalize(position)) * forward;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		forward = glm::angleAxis(deltatime * -1.0_f32, glm::normalize(position)) * forward;
	}

	velocity += gravityStrength * -glm::normalize(position) * deltatime;
	glm::fvec3 new_position = position + velocity * deltatime;
	
	f32 height = world.GetHeight(new_position);
	DebugPrint(std::to_string(glm::length(new_position)));
	glm::fvec3 heightvec = height * glm::normalize(new_position);
	if (glm::length(new_position) < height)
	{
		new_position = heightvec;
		velocity = glm::fvec3();
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
	// TODO snap to closest orthogonal

	position = new_position;
	forward = new_forward;
}