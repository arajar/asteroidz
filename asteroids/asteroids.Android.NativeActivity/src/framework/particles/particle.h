#pragma once
#include "state.h"

namespace particles
{
	struct state;

	struct particle
	{
		state					m_state;
		glm::vec4				m_color;
		glm::vec2				m_pos;
		float					m_scale = 1.f;
		float					m_dir;
		float					m_duration;
		float					m_percentLife = 1.f;
	};
}