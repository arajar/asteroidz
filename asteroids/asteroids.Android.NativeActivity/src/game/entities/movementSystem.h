#pragma once

#include "entity.h"

namespace e
{
	// Movement system
	// Modifies the position of the entity by taking the direction, acceleration and delta time
	struct movementSystem : public ecs::system
	{
		math::vec2 m_size;

		movementSystem(ecs::world& world) : ecs::system(world) {}

		void setWindowSize(const math::vec2& size) { m_size = size; }

		void operator()(float delta)
		{
			// apply the local rotation for the asteroids and asteroid chunks
			for (auto& en : m_world.search<localRotation>())
			{
				auto r = m_world.get<localRotation>(en);

				r->rotation += r->rotSpeed * delta;
				if (r->rotation > 360.f)
				{
					r->rotation -= 360.f;
				}
				else if (r->rotation < 0)
				{
					r->rotation += 360.f;
				}
			}

			// move all the entities (ship, asteroids and asteroid chunks)
			for (auto& en : m_world.search<position, direction, acceleration>())
			{
				auto p = m_world.get<position>(en);
				auto d = m_world.get<direction>(en);
				auto a = m_world.get<acceleration>(en);

				move(p->pos, d->angle, a->acc, delta);
			}

			// move the missiles
			for (auto& en : m_world.search<missileArray>())
			{
				auto missiles = m_world.get<missileArray>(en);

				for (size_t i = 0; i < missiles->missiles.size(); ++i)
				{
					auto& mis = missiles->missiles[i];
					move(mis.pos, mis.dir, mis.acc, delta);
				}
			}
		}

		// moves the entity and also checks the bounds of the map
		void move(math::vec2& pos, float dir, float acc, float delta)
		{
			pos.x += std::sin(-dir) * acc * delta;
			pos.y += std::cos(-dir) * acc * delta;

			if (pos.x > m_size.x)
			{
				pos.x -= m_size.x;
			}

			if (pos.x < 0)
			{
				pos.x += m_size.x;
			}

			if (pos.y > m_size.y)
			{
				pos.y -= m_size.y;
			}

			if (pos.y < 0)
			{
				pos.y += m_size.y;
			}
		}
	};
}