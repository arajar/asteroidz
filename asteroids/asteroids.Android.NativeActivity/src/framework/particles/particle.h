#pragma once

namespace ps
{
	struct particle
	{
		struct state			m_state;
		math::vec4				m_color;
		math::vec2				m_pos;
		float					m_scale = 1.f;
		float					m_dir;
		float					m_duration;
		float					m_percentLife = 1.f;
	};
}