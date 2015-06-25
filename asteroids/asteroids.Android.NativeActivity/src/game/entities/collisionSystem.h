#pragma once

#include "entity.h"

namespace e
{
	// Collision system
	struct collisionSystem : public ecs::system
	{
		collisionSystem(ecs::world& world) : ecs::system(world) {}

		void operator()(float delta) const
		{
			auto entities = m_world.search<position, collision>();
			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				ecs::entity e1 = *it;

				const auto p1 = m_world.get<position>(e1);
				auto c1 = m_world.get<collision>(e1);

				for (auto it2 = entities.begin() + 1; it2 != entities.end(); it2++)
				{
					ecs::entity e2 = *it2;

					const auto p2 = m_world.get<position>(e1);
					auto c2 = m_world.get<collision>(e1);

					const auto distance = p1->pos - p2->pos;
					const float length = m::vec2::length(distance);
					const float totalRadius = c1->colRadius + c2->colRadius;
					if (length <= totalRadius)
					{
						c1->collided = true;
						c2->collided = true;
					}
				}
			}
		}
	};
}