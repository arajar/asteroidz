#pragma once

namespace ps
{
	struct particle;

	struct state
	{
		enum class type
		{
			None,
			Enemy,
			Bullet,
		};

		glm::vec2		m_vel;
		type			m_type;
		float			m_lenMultiplier = 1.f;

		state() {}
		state(const glm::vec2& vel, type t, float lenMultiplier = 1.f) : m_vel(vel), m_type(t), m_lenMultiplier(lenMultiplier) {}

		static state	getRandom(float min, float max);
		void			update(particle& p);
	};
}
