#pragma once

#include "entity.h"

namespace e
{
	// shooting system
	// takes the angle from the specified virtual joystick and shoots a missile in that direction
	struct shootSystem : public ecs::system
	{
	private:
		const input::virtualJoystick* m_joy = nullptr;
		float m_timeSinceLastShoot = 0.f;
		const float m_timeToShoot = 10.f;
		const float m_maxMissileTime = 50.f;

	public:
		shootSystem(ecs::world& world) : ecs::system(world) {}
		void setJoy(const input::virtualJoystick* joy) { m_joy = joy; }

		void operator()(float delta)
		{
			m_timeSinceLastShoot += delta;

			for (auto& en : m_world.search<e::missileArray, e::position>())
			{
				auto m = m_world.get<missileArray>(en);
				const auto p = m_world.get<position>(en);

				// update the missiles
				// first checks if any missile needs to be removed
				for (auto it = m->missiles.begin(); it != m->missiles.end(); )
				{
					auto& missile = (*it);
					missile.time += delta;
					if (missile.time >= m_maxMissileTime)
					{
						it = m->missiles.erase(it);
					}
					else
					{
						it++;
					}
				}

				// then checks if we can shoot a new missile
				if (m_joy->m_isTouching && m_timeSinceLastShoot >= m_timeToShoot)
				{
					shoot(m, p->pos, m_joy->m_angle);
					m_timeSinceLastShoot = 0.f;
				}
			}
		}

		// creates a new missile in the specified position and direction
		void shoot(missileArray* m, const math::vec2& pos, float direction)
		{
			missileArray::data missile;
			missile.pos = pos;
			missile.acc = 15.f;
			missile.dir = -direction;
			missile.time = 0.f;

			m->missiles.push_back(missile);
		}
	};
}
