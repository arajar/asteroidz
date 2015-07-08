#pragma once

namespace ps
{
	struct state;
	struct particle;

	class manager
	{
	public:
		static void init(const math::mat4& projection);

		static void update();
		static void render();

		static void createParticle(const math::vec2& pos, const math::vec4& color, float duration, float scale, const state& state, float angle = 0);

		static void clear();

		static size_t getParticleCount();

	protected:
		static void swap(util::circularArray<particle>& list, size_t index1, size_t index2);

	protected:
		static util::circularArray<particle> m_particleList;
		static GLuint			m_vbo;
		static gfx::shader		m_shader;
		static gfx::texture		m_texture;
		static math::mat4		m_projection;
	};
}