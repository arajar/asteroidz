#pragma once

#include "entity.h"

namespace e
{
	// Collision system
	struct collisionSystem : public ecs::system
	{
		collisionSystem(ecs::world& world) : ecs::system(world) {}

		void operator()(float delta)
		{
			std::vector<ecs::entity> collidedEntities;

			// First detect and mark all the collisions
			auto entities = m_world.search<position, collision, entityType>();
			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				ecs::entity e1 = *it;
				auto c1 = m_world.get<collision>(e1);
				if (c1->collided) { continue; }

				const auto et1 = m_world.get<entityType>(e1);
				const auto p1 = m_world.get<position>(e1);

				// check collisions for asteroids vs missiles
				for (auto& mis : m_world.search<missileArray>())
				{
					auto m = m_world.get<missileArray>(mis);

					for (size_t i = 0; i < m->missiles.size(); ++i)
					{
						auto missile = m->missiles[i];
						const auto distance = p1->pos - missile.pos;
						const float length = math::length(distance);
						const float totalRadius = c1->colRadius + m->radius;
						if (length <= totalRadius)
						{
							if (et1->type != EntityType::Player)
							{
								c1->collided = true;
								collidedEntities.push_back(e1);
							}

							missile.collided = true;
						}
					}
				}
			}

			// check asteroid vs ship collisions 
			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				ecs::entity e1 = *it;

				auto c1 = m_world.get<collision>(e1);
				if (c1->collided) { continue; }

				const auto et1 = m_world.get<entityType>(e1);
				const auto p1 = m_world.get<position>(e1);

				for (auto it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					ecs::entity e2 = *it2;
					if (e1 == e2) { continue; }

					auto c2 = m_world.get<collision>(e2);
					if (c2->collided) { continue; }

					const auto et2 = m_world.get<entityType>(e2);

					// we only want to check collisions between different kinds of entities
					if (et1->type == et2->type
						|| (et1->type == EntityType::Asteroid      && et2->type == EntityType::AsteroidChunk)
						|| (et1->type == EntityType::AsteroidChunk && et2->type == EntityType::Asteroid))
					{
						continue;
					}

					const auto p2 = m_world.get<position>(e2);

					const auto distance = p1->pos - p2->pos;
					const float length = math::length(distance);
					const float totalRadius = c1->colRadius + c2->colRadius;
					if (length <= totalRadius)
					{
						// uncomment this line to make the player immortal, useful to debug
						//if (et1->type != EntityType::Player)
						{
							c1->collided = true;
							collidedEntities.push_back(e1);
						}

						// uncomment this line to make the player immortal, useful to debug
						//if (et2->type != EntityType::Player)
						{
							c2->collided = true;
							collidedEntities.push_back(e2);
						}
					}
				}
			}

			// Then for every collision, react
			for (auto& e : collidedEntities)
			{
				auto acc = m_world.get<acceleration>(e);
				if (acc)
				{
					acc->acc = 0.f;
				}

				auto localRot = m_world.get<localRotation>(e);
				if (localRot)
				{
					localRot->rotSpeed = 0.f;
				}

				auto type = m_world.get<entityType>(e);
				if (type)
				{
					type->alive = false;
				}
			}
		}
	};
}