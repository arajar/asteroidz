#pragma once

#include "entity.h"

namespace e
{
	struct movement : public ecs::system
	{
		movement(ecs::world& world) : ecs::system(world) {}

		void operator()(float delta) const
		{
			for (auto& en : m_world.search<position, direction, acceleration>())
			{
				auto p = m_world.get<position>(en);
				auto d = m_world.get<direction>(en);
				auto a = m_world.get<acceleration>(en);

				p->pos.x += d->dir.x * a->acc * delta;
				p->pos.y += d->dir.y * a->acc * delta;
			}
		}
	};
}