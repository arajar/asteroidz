#pragma once

namespace particles
{
	struct state;
	struct particle;

	class manager
	{
	public:
		manager(int capacity);

		void update();
		void render();

		void createParticle(gfx::texture* tex, const glm::vec2& pos, const glm::vec4& color, float duration, float scale, const state& state, float angle = 0);

		void clear();

		size_t getParticleCount();

	protected:
		void swap(util::circularArray<particle>& list, size_t index1, size_t index2);

	protected:
		util::circularArray<particle> m_particleList;
	};
}