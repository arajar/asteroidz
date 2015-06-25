#pragma once

#include "entity.h"

namespace e
{
	// Movement system
	// Modifies the position of the entity by taking the angle, acceleration and delta time
	struct movementSystem : public ecs::system
	{
		m::vec2 m_size;

		movementSystem(ecs::world& world) : ecs::system(world) {}

		void setWindowSize(const m::vec2& size) { m_size = size; }

		void operator()(float delta) const
		{
			for (auto& en : m_world.search<position, direction, acceleration>())
			{
				auto p = m_world.get<position>(en);
				auto d = m_world.get<direction>(en);
				auto a = m_world.get<acceleration>(en);

				p->pos.x += std::cos(m::toRad(d->angle)) * a->acc * delta;
				p->pos.y += std::sin(m::toRad(d->angle)) * a->acc * delta;

				if (p->pos.x > m_size.x) { p->pos.x -= m_size.x; }
				if (p->pos.x < 0) { p->pos.x += m_size.x; }
				if (p->pos.y > m_size.y) { p->pos.y -= m_size.y; }
				if (p->pos.y < 0) { p->pos.y += m_size.y; }
			}
		}
	};
}