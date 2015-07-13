#pragma once

#include "entity.h"

namespace e
{
	// spawn system
	struct spawnSystem : public ecs::system
	{
		spawnSystem(ecs::world& world) : ecs::system(world) {}

		int minAsteroids = 5;
		math::vec2 m_size;

		void setWindowSize(const math::vec2& size) { m_size = size; }

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
					std::mt19937 rng(rd());
					std::uniform_real_distribution<float> rand(1.f, 10.f);

					// if the asteroid is destroyed, spawn a random number of chunks at the same position
					// and remove the asteroid
					if (typ->type == EntityType::Asteroid)
					{
						const auto pos = m_world.get<e::position>(en);
						spawnAsteroidChunk(pos->pos);

						// create an explosion with particles
						for (int i = 0; i < 20; ++i)
						{
							float speed = 18.f * (1.f - 1 / rand(rng));
							ps::state state = ps::state::getRandom(speed, speed);
							state.m_type = ps::state::type::Enemy;

							math::vec4 color(1.0f, 0.0f, 0.0f, 1.f);
							ps::manager::createParticle(pos->pos, color, 50.f, 1.5f, state);
						}

						m_world.removeEntity(en);
					}
					else if (typ->type == EntityType::AsteroidChunk)
					{
						// if its a chunk, remove it directly without spawning new chunks
						const auto pos = m_world.get<e::position>(en);

						for (int i = 0; i < 20; ++i)
						{
							float speed = 18.f * (1.f - 1 / rand(rng));
							ps::state state = ps::state::getRandom(speed, speed);
							state.m_type = ps::state::type::Enemy;

							math::vec4 color(0.8f, 0.2f, 0.2f, 1.f);
							ps::manager::createParticle(pos->pos, color, 40.f, 1.0f, state);
						}

						m_world.removeEntity(en);
					}
					else if (typ->type == EntityType::Player)
					{
						const auto pos = m_world.get<e::position>(en);
						for (int i = 0; i < 40; ++i)
						{
							float speed = 18.f * (1.f - 1 / rand(rng));
							ps::state state = ps::state::getRandom(speed, speed);
							state.m_type = ps::state::type::Enemy;

							math::vec4 color(0.8f, 0.2f, 0.2f, 1.f);
							ps::manager::createParticle(pos->pos, color, 70.f, 1.0f, state);
						}
					}
				}
			}

			// check that there are at least the min number of asteroids spawned
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

			pos->pos = math::vec2(posX(rng), posY(rng));
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
		void spawnAsteroidChunk(const math::vec2& parentPos)
		{
			std::mt19937 rng(rd());
			std::uniform_real_distribution<float> angle(0.f, 360.f);
			std::uniform_real_distribution<float> speed(5.f, 7.f);
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