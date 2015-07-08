#pragma once

namespace gfx
{
	struct texturedBox
	{
		~texturedBox();

		void init(const std::string& name);
		void render(const math::mat4& projection);

	protected:
		gfx::shader*	m_shader = nullptr;
		gfx::texture*	m_texture = nullptr;
		GLuint			m_vbo = 0;
	};
}