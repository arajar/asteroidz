#include "virtual_joystick.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////////

namespace input
{
	void virtualJoystick::init()
	{
		m_background = new e::renderable;
		m_thumb = new e::renderable;

		util::createCircle(m_background);
		util::createCircle(m_thumb);
	}

	//////////////////////////////////////////////////////////////////////////

	void virtualJoystick::handleInput(float x, float y)
	{
		float dx = x - m_position.x;
		float dy = y - m_position.y;
		float distance = std::sqrt(dx*dx + dy*dy);
		float angle = std::atan2f(dx, dy);

		m_isTouching = (m_radius >= distance);

		m_oldPosition = m_touchPosition;
		m_touchPosition = { x, y };

		m_delta = m_touchPosition - m_oldPosition;

		if (m_isTouching)
		{
			dx = std::cos(angle) * m_radius;
			dy = std::sin(angle) * m_radius;
		}

		m_velocity = {dx / m_radius, dy / m_radius};

		int mask = 0;
		if (m_velocity.x > m_cuadrantSize)
		{
			mask = (int)Direction::LEFT;
		}
		else if (m_velocity.x < m_cuadrantSize)
		{
			mask = (int)Direction::RIGHT;
		}

		if (m_velocity.y < m_cuadrantSize)
		{
			mask &= (int)Direction::TOP;
		}
		else if (m_velocity.y > m_cuadrantSize)
		{
			mask &= (int)Direction::BOTTOM;
		}

		m_currentDirection = (Direction)mask;

		if (distance > m_thumbRadius)
		{
			m_thumbPosition.x = m_position.x + std::cos(angle) * m_thumbRadius;
			m_thumbPosition.y = m_position.y + std::sin(angle) * m_thumbRadius;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void virtualJoystick::render(const gfx::camera& cam)
	{
		draw(cam, *m_background, m_position, m_radius);
		draw(cam, *m_thumb, m_thumbPosition, m_thumbRadius);
	}

	void virtualJoystick::draw(const gfx::camera& cam, const e::renderable& r, const m::vec2& pos, float radius)
	{
		const m::mat4 transform = m::mat4::translate(m::mat4(1), m::vec3(pos)) * m::mat4::scale(m::mat4(), m::vec3(10));

		// future optimization: bind the shader only once to avoid binding and unbinding the same shader
		glBindBuffer(GL_ARRAY_BUFFER, r.vbo);

		glEnableVertexAttribArray(r.shader->attribute("vert"));
		glVertexAttribPointer(r.shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

		r.shader->begin();
		r.shader->uniform("model", transform);
		r.shader->uniform("camera", cam.matrix());
		r.shader->uniform("color", m::vec3(1.0, 0.0, 0.0));
		r.shader->uniform("radius", radius);
		glDrawArrays(r.type, 0, r.numOfPolys);
		r.shader->end();

		glDisableVertexAttribArray(r.shader->attribute("vert"));
		glDisableVertexAttribArray(r.shader->attribute("color"));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}