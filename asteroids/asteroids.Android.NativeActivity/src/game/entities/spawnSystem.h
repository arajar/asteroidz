#pragma once

#include "entity.h"

namespace e
{
	// Collision system
	struct spawnSystem : public ecs::system
	{
		spawnSystem(ecs::world& world) : ecs::system(world) {}

		int minAsteroids = 5;
		glm::vec2 m_size;

		void setWindowSize(const glm::vec2& size) { m_size = size; }

		void operator()(float delta)
		{
			int num = 0;
			const auto& entities = m_world.search<e::entityType>();
			for (auto& en : entities)
			{
				// checks which asteroids are still "alive"
				const auto typ = m_world.get<e::entityType>(en);
				if (typ->type == EntityType::Asteroid && typ->alive)
				{
					num++;
				}

				if (!typ->alive)
				{
					// if the asteroid is destroyed, spawn a random number of chunks at the same position
					// and remove the asteroid
					if (typ->type == EntityType::Asteroid)
					{
						const auto pos = m_world.get<e::position>(en);
						spawnAsteroidChunk(pos->pos);
						m_world.removeEntity(en);
					}
					else if (typ->type == EntityType::AsteroidChunk)
					{
						// if its a chunk, remove it directly without spawning anything
						m_world.removeEntity(en);
					}
				}
			}

			// check there are at least the min number of asteroids spawned
			while (num < minAsteroids)
			{
				spawnAsteroid();
				++num;
			}
		}

	protected:
		std::random_device rd;

		// create an asteroid entity with random values
		void spawnAsteroid()
		{
			std::mt19937 rng(rd());
			std::uniform_real_distribution<float> angle(0.f, 360.f);
			std::uniform_real_distribution<float> posX(0.f, m_size.x);
			std::uniform_real_distribution<float> posY(0.f, m_size.y);
			std::uniform_real_distribution<float> speed(2.f, 7.f);
			std::uniform_int_distribution<int> rotAngle(-1, 1);

			auto asteroid = m_world.createEntity();

			auto pos = m_world.add<e::position>(asteroid);
			auto dir = m_world.add<e::direction>(asteroid);
			auto col = m_world.add<e::collision>(asteroid);
			auto ren = m_world.add<e::renderable>(asteroid);
			auto acc = m_world.add<e::acceleration>(asteroid);
			auto rot = m_world.add<e::localRotation>(asteroid);
			auto typ = m_world.add<e::entityType>(asteroid);

			pos->pos = glm::vec2(posX(rng), posY(rng));
			dir->angle = angle(rng);
			col->colRadius = 50.f;
			util::createAsteroid(ren, 10.f);
			acc->acc = speed(rng);
			rot->rotSpeed = 0.09f * rotAngle(rng);
			typ->alive = true;
			typ->type = EntityType::Asteroid;
#if defined DEBUG_COLLISIONS
			auto deb = m_world.add<e::debugRenderable>(asteroid);
			util::createDebugCircle(deb, col->colRadius);
#endif
		}

		// create an asteroid chunk entity with random values
		void spawnAsteroidChunk(const glm::vec2& parentPos)
		{
			std::mt19937 rng(rd());
			std::uniform_real_distribution<float> angle(0.f, 360.f);
			std::uniform_real_distribution<float> speed(5.f, 8.f);
			std::uniform_int_distribution<int> rotAngle(-1, 1);
			std::uniform_int_distribution<int> num(1, 3);

			for (int i = 0; i < num(rng); ++i)
			{
				auto asteroid = m_world.createEntity();

				auto pos = m_world.add<e::position>(asteroid);
				auto dir = m_world.add<e::direction>(asteroid);
				auto col = m_world.add<e::collision>(asteroid);
				auto ren = m_world.add<e::renderable>(asteroid);
				auto acc = m_world.add<e::acceleration>(asteroid);
				auto rot = m_world.add<e::localRotation>(asteroid);
				auto typ = m_world.add<e::entityType>(asteroid);

				pos->pos = parentPos;
				dir->angle = angle(rng);
				col->colRadius = 16.f;
				util::createAsteroid(ren, 4.f);
				acc->acc = speed(rng);
				rot->rotSpeed = 0.09f * rotAngle(rng);
				typ->alive = true;
				typ->type = EntityType::AsteroidChunk;
#if defined DEBUG_COLLISIONS
				auto deb = m_world.add<e::debugRenderable>(asteroid);
				util::createDebugCircle(deb, col->colRadius);
#endif
			}
		}
	};
}