#include "virtual_joystick.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////////

namespace input
{
	void virtualJoystick::init()
	{
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

	void virtualJoystick::render()
	{
	}
}