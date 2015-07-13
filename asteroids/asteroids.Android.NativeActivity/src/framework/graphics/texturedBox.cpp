#include "texturedBox.h"

namespace gfx
{
	texturedBox::~texturedBox()
	{
		if (m_texture)
		{
			delete m_texture;
			m_texture = nullptr;
		}

		if (m_shader)
		{
			delete m_shader;
			m_shader = nullptr;
		}

		if (m_vbo != 0)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0;
		}
	}

	void texturedBox::init(const std::string& name)
	{
		m_texture = new gfx::texture;
		m_texture->load(name);

		m_shader = new gfx::shader;
		m_shader->vertex("particle.vs.glsl").pixel("particle.ps.glsl").link();

		GLfloat vertices[] = {
			//  pos       tex
			0.f, 1.f, 0.f, 1.f,
			1.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 0.f,

			0.f, 1.f, 0.f, 1.f,
			1.f, 1.f, 1.f, 1.f,
			1.f, 0.f, 1.f, 0.f
		};

		// create the vbo and bind the attributes
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(m_shader->attribute("vert"));
		glVertexAttribPointer(m_shader->attribute("vert"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glDisableVertexAttribArray(m_shader->attribute("vert"));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void texturedBox::render(const math::mat4& projection, const math::vec2& size)
	{
		m_shader->begin();
		m_texture->begin();
		m_texture->disableBlending();

		m_shader->uniform("projection", projection);

		math::mat4 model = math::translate(math::mat4(), math::vec3(size.x, size.y, -0.2));
		model *= math::scale(math::mat4(), math::vec3(size.x, size.y, 1.f));
		model *= math::scale(math::mat4(), math::vec3(-1));

		m_shader->uniform("model", model);
		m_shader->uniform("color", math::vec4(1.f, 1.f, 1.f, 1.f));

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glEnableVertexAttribArray(m_shader->attribute("vert"));
		glVertexAttribPointer(m_shader->attribute("vert"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(m_shader->attribute("vert"));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_texture->end();
		m_shader->end();
	}
}