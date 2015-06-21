#pragma once

namespace gfx
{
	struct fbo
	{
		fbo(const m::vec2& resolution) : m_fbo(-1), m_fboTexture(-1), m_depthBuffer(-1), m_vbo(-1)
			, m_shader(nullptr), m_resolution(resolution) {}

		void init(gfx::shader* shader);

		void begin();
		void end();

		void render();

	protected:
		GLuint m_fbo;
		GLuint m_fboTexture;
		GLuint m_depthBuffer;

		GLuint m_vbo;

		gfx::shader* m_shader;

		m::vec2 m_resolution;
	};
}