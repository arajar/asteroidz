#pragma once

namespace e
{
	struct position : public ecs::component
	{
		m::vec2 pos;
	};

	struct direction : public ecs::component
	{
		float angle = 0.f;
	};

	struct acceleration : public ecs::component
	{
		float acc = 0.f;
	};

	struct collision : public ecs::component
	{
		std::vector<m::vec2> pointCloud;
		float colRadius = 0.f;
		bool collided = false;
	};

	struct player : public ecs::component
	{
		bool dead = false;
	};

	struct renderable : public ecs::component
	{
		GLuint vbo;
		gfx::shader* shader;
		GLuint numOfPolys;
		GLuint type;
	};
}