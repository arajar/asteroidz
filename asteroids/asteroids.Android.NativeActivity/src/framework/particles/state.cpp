#include "state.h"
#include "particle.h"

namespace ps
{
	state state::getRandom(float min, float max)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float> rand;

		float t = rand(rng) * 2.f * math::pi<float>();
		float len = rand(rng) * (max - min) + min;

		return state(math::vec2(len * std::cos(t), len * sin(t)), type::None, 1);
	}

	void state::update(particle& p)
	{
		math::vec2 vel = p.m_state.m_vel;
		float speed = math::length(vel);

		p.m_pos += vel;

		float alpha = std::min(1.f, std::min(p.m_percentLife * 2, speed * 1.f));
		alpha *= alpha;

		p.m_color.a = alpha;

		if (p.m_state.m_type == type::Bullet)
		{
			p.m_scale = p.m_state.m_lenMultiplier * std::min(std::min(1.f, 0.1f * speed + 0.1f), alpha);
		}
		else
		{
			p.m_scale *= 0.94f;
		}

		p.m_dir = std::atan2(vel.x, vel.y);
		
		if (std::abs(vel.x) + std::abs(vel.y) < 0.00000000001f)
		{
			vel = { 0, 0 };
		}
		else if (p.m_state.m_type == type::Enemy)
		{
			vel *= 0.94f;
		}
		else
		{
			vel *= 0.96f + std::fmodf(std::abs(p.m_pos.x), 0.04f);
		}
		
		p.m_state.m_vel = vel;
		
	}
}