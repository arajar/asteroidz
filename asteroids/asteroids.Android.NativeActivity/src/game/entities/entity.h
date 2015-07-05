#pragma once

namespace e
{
	enum class EntityType
	{
		Asteroid,
		AsteroidChunk,
		Missile,
		Player,

		None,
	};

	struct position : public ecs::component
	{
		//m::vec2 pos;
		glm::vec2 pos;
	};

	struct localRotation : public ecs::component
	{
		float rotation = 0.f;
		float rotSpeed = 0.f;
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
		float colRadius = 0.f;
		bool collided = false;
	};

	struct entityType : public ecs::component
	{
		EntityType type = EntityType::None;
		bool alive = true;
	};

	struct renderable : public ecs::component
	{
		GLuint vbo;
		gfx::shader* shader;
		GLuint numOfPolys;
		GLuint type;
	};

#if defined DEBUG_COLLISIONS
	struct debugRenderable : public ecs::component
	{
		GLuint vbo;
		gfx::shader* shader;
		GLuint numOfPolys;
		GLuint type;
	};
#endif

	struct missileArray : public ecs::component
	{
		renderable			ren;
		float				radius;

		struct data
		{
			glm::vec2		pos = { 0,0 };
			float			dir = 0.f;
			float			acc = 0.f;
			float			time = 0.f;
			bool			collided = false;
		};

		std::vector<data>	missiles;
#if defined DEBUG_COLLISIONS
		debugRenderable*			deb;
#endif
	};
}