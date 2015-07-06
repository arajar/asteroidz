#include "virtual_joystick.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////////

namespace input
{
	void virtualJoystick::init(float radius)
	{
		m_radius = radius;

		m_thumbRadius = m_radius - (m_radius * 0.20f);

		m_background = new e::renderable;
		m_thumb = new e::renderable;

		util::createCircle(m_background, m_radius);
		util::createCircle(m_thumb, m_thumbRadius);

		auto QuadEaseOut = [](float val)
		{
			float invVal = 1.0f - val;
			invVal *= invVal; // invVal^2
			return 1.0f - invVal;
		};

		m_alpha.setEaseFunction(QuadEaseOut);
		m_alpha.reset(0.f, 0.f);
		m_alpha.setDelay(10); // milliseconds
	}

	//////////////////////////////////////////////////////////////////////////

	void virtualJoystick::handleInput(const input::TouchEvent& ev)
	{
		float dx = ev.x - m_position.x;
		float dy = ev.y - m_position.y;
		float distance = std::sqrt(dx*dx + dy*dy);
		m_angle = std::atan2f(dx, dy);

		m_alpha.reset(ev.alpha, 0.f);

		m_isTouching = (m_radius >= distance) && ev.action != input::Action::Up;

		m_oldPosition = m_touchPosition;
		m_touchPosition = { ev.x, ev.y };

		m_delta = m_touchPosition - m_oldPosition;

		dx = std::sin(m_angle) * m_radius;
		dy = std::cos(m_angle) * m_radius;

		m_velocity = { dx / m_radius, dy / m_radius };

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

		m_thumbPosition = m_touchPosition;

		if (distance > m_radius)
		{
			m_thumbPosition.x = m_position.x + glm::sin(m_angle) * m_radius;
			m_thumbPosition.y = m_position.y + glm::cos(m_angle) * m_radius;
		}

		float dist = glm::clamp(distance, 0.f, m_radius);
		m_acceleration = dist / m_radius;
	}

	//////////////////////////////////////////////////////////////////////////

	void virtualJoystick::render()
	{
		draw(*m_background, m_position);
		draw(*m_thumb, m_thumbPosition);
	}

	void virtualJoystick::update(float deltaTime)
	{
		m_alpha.update(deltaTime);
	}

	void virtualJoystick::draw(const e::renderable& r, const glm::vec2& pos)
	{
		const glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(pos, 0.f));

		// future optimization: bind the shader only once to avoid binding and unbinding the same shader
		glBindBuffer(GL_ARRAY_BUFFER, r.vbo);

		glEnableVertexAttribArray(r.shader->attribute("vert"));
		glVertexAttribPointer(r.shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

		r.shader->begin();
		r.shader->uniform("model", transform);
		r.shader->uniform("camera", m_projection);
		r.shader->uniform("finalColor", glm::vec4(m_alpha.getValue()));
		glDrawArrays(r.type, 0, r.numOfPolys);
		r.shader->end();

		GLenum error = glGetError();
		if (error != GL_NONE)
		{
			LOGE("Error %d rendering the joystick", error);
		}

		glDisableVertexAttribArray(r.shader->attribute("vert"));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}