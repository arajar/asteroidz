#pragma once

namespace e
{
	struct position : public ecs::component
	{
		m::vec2 pos;
	};

	struct direction : public ecs::component
	{
		m::vec2 dir;
	};

	struct acceleration : public ecs::component
	{
		float acc = 0.f;
	};

	struct constantAcceleration : public ecs::component
	{
		float acc = 0.f;
	};

	struct collision : public ecs::component
	{
		std::vector<m::vec2> pointCloud;
		float colRadius = 0.f;
	};

	struct player : public ecs::component
	{
		bool dead = false;
	};
}