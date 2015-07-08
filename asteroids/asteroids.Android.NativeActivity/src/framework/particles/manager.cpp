#include "manager.h"
#include "particle.h"

namespace ps
{
	util::circularArray<particle> manager::m_particleList(300);
	GLuint			manager::m_vbo = 0;
	gfx::shader		manager::m_shader;
	gfx::texture	manager::m_texture;
	math::mat4		manager::m_projection;

	void manager::init(const math::mat4& projection)
	{
		m_projection = projection;
		m_shader.vertex("particle.vs.glsl").pixel("particle.ps.glsl").link();

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

		glEnableVertexAttribArray(m_shader.attribute("vert"));
		glVertexAttribPointer(m_shader.attribute("vert"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glDisableVertexAttribArray(m_shader.attribute("vert"));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_texture.load("particletexture.bmp");
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
		m_shader.begin();
		m_shader.uniform("projection", m_projection);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(m_shader.attribute("vert"));
		glVertexAttribPointer(m_shader.attribute("vert"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		// future optimization: batch the particle rendering
		math::vec2 size = m_texture.getSize();
		m_texture.begin();
		m_texture.enableBlending();
		for (size_t i = 0; i < m_particleList.getCount(); ++i)
		{
			auto particle = m_particleList[i];

			// first translate
			math::mat4 model = math::translate(math::mat4(), math::vec3(particle.m_pos.x, particle.m_pos.y, 0.f));
			// then move the origin of rotation to center of the quad
			model = math::translate(model, math::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
			// then rotate
			model = math::rotate(model, -particle.m_dir, math::vec3(0.f, 0.f, 1.f));
			// move the origin back
			model = math::translate(model, math::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
			// scale
			model = math::scale(model, math::vec3(size.x * particle.m_scale, size.y * particle.m_scale, 1.f));
			m_shader.uniform("model", model);
			m_shader.uniform("color", particle.m_color);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		m_texture.disableBlending();
		m_texture.end();

		glDisableVertexAttribArray(m_shader.attribute("vert"));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_shader.end();
	}

	void manager::createParticle(const math::vec2& pos, const math::vec4& color, float duration, float scale, const state& state, float angle)
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