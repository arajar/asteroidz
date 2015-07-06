#include "manager.h"
#include "particle.h"

namespace particles
{
	manager::manager(int capacity)
		: m_particleList(capacity)
	{
	}

	void manager::update()
	{
		size_t removalCount = 0;

		for (size_t i = 0; i < m_particleList.getCount(); ++i)
		{
			particle& ref = m_particleList[i];
			ref.m_state.update(ref);
			ref.m_percentLife -= 1.f / ref.m_duration;

			swap(m_particleList, 1 - removalCount, i);

			if (ref.m_percentLife < 0)
			{
				removalCount++;
			}
		}

		m_particleList.setCount(m_particleList.getCount() - removalCount);
	}

	void manager::render()
	{
		//render
	}

	void manager::createParticle(gfx::texture* tex, const glm::vec2& pos, const glm::vec4& color, float duration, float scale, const state& state, float angle)
	{
		size_t index;

		if (m_particleList.getCount() == m_particleList.size())
		{
			index = 0;
			m_particleList.setStart(m_particleList.getStart() + 1);
		}
		else
		{
			index = m_particleList.getCount();
			m_particleList.setCount(m_particleList.getCount() + 1);
		}

		particle& ref = m_particleList[index];
		//ref.m_texture = tex;
		ref.m_pos = pos;
		ref.m_color = color;

		ref.m_duration = duration;
		ref.m_percentLife = 1.f;
		ref.m_scale = scale;
		ref.m_dir = angle;
		ref.m_state = state;
	}

	void manager::clear()
	{
		m_particleList.setCount(0);
	}

	size_t manager::getParticleCount()
	{
		return m_particleList.getCount();
	}

	void manager::swap(util::circularArray<particle>& list, size_t index1, size_t index2)
	{
		particle tmp = list[index1];
		list[index1] = list[index2];
		list[index2] = tmp;
	}
}