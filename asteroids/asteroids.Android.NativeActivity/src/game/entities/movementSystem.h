#pragma once

#include "entity.h"

namespace e
{
	// Movement system
	// Modifies the position of the entity by taking the angle, acceleration and delta time
	struct movementSystem : public ecs::system
	{
		glm::vec2 m_size;

		movementSystem(ecs::world& world) : ecs::system(world) {}

		void setWindowSize(const glm::vec2& size) { m_size = size; }

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

			for (auto& en : m_world.search<position, entityType>())
			{
				auto t = m_world.get<entityType>(en);
				if (t->type == EntityType::Player)
				{
					const auto p = m_world.get<position>(en);
					const auto d = m_world.get<direction>(en);
					addTrailParticles(p->pos, d->angle, delta);
				}
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
		void move(glm::vec2& pos, float dir, float acc, float delta)
		{
			pos.x += glm::sin(-dir) * acc * delta;
			pos.y += glm::cos(-dir) * acc * delta;

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

		void addTrailParticles(const glm::vec2& pos, float angle, float deltaTime)
		{
			glm::vec4 sideColor(0.78f, 0.15f, 0.04f, 1);
			glm::vec4 midColor(1.0f, 0.73f, 0.12f, 1);
			const float alpha = 0.7f;

			glm::vec2 rot(pos.x + std::sin(angle), pos.y + std::cos(angle));

			glm::vec2 vel(10.f);
			glm::vec2 baseVel = vel * (-3.f / vel.length());
			glm::vec2 perpVel = glm::vec2(baseVel.y, -baseVel.x) * (0.6f * std::sin(deltaTime * 10.f));

			glm::vec2 finalPos = (pos + rot) / 2.f;

			// middle particle stream
			glm::vec2 velMid = baseVel;
			ps::manager::createParticle(finalPos, glm::vec4(1, 1, 1, 1) * alpha, 30.0f, 1.f, ps::state(velMid, ps::state::type::Enemy));
			ps::manager::createParticle(finalPos, midColor * alpha, 30.0f, 1.f, ps::state(velMid, ps::state::type::Enemy));

			// side particle streams
			//tVector2f vel1 = baseVel + perpVel + Extensions::nextVector2(0, 0.3f);
			//tVector2f vel2 = baseVel - perpVel + Extensions::nextVector2(0, 0.3f);
			//GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(),
			//	pos, tColor4f(1, 1, 1, 1) * alpha, 60.0f, tVector2f(0.5f, 1),
			//	ParticleState(vel1, ParticleState::kEnemy));
			//GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(),
			//	pos, tColor4f(1, 1, 1, 1) * alpha, 60.0f, tVector2f(0.5f, 1),
			//	ParticleState(vel2, ParticleState::kEnemy));

			//GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getGlow(),
			//	pos, sideColor * alpha, 60.0f, tVector2f(0.5f, 1),
			//	ParticleState(vel1, ParticleState::kEnemy));
			//GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getGlow(),
			//	pos, sideColor * alpha, 60.0f, tVector2f(0.5f, 1),
			//	ParticleState(vel2, ParticleState::kEnemy));
		}
	};
}