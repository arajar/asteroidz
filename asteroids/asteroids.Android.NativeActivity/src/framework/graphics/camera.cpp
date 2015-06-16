#include "camera.h"

namespace gfx
{
	static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

	camera::camera()
		: m_position(0.0f, 0.0f, 1.0f)
		, m_horizontalAngle(0.0f)
		, m_verticalAngle(0.0f)
		, m_fieldOfView(55.0f)
		, m_nearPlane(0.0001f)
		, m_farPlane(10000.0f)
		, m_viewportAspectRatio(4.0f / 3.0f)
	{
	}

	const m::vec3& camera::getPosition() const
	{
		return m_position;
	}

	void camera::setPosition(const m::vec3& position)
	{
		m_position = position;
	}

	void camera::setOffsetPosition(const m::vec3& offset)
	{
		m_position += offset;
	}

	float camera::getFov() const
	{
		return m_fieldOfView;
	}

	void camera::setFov(float fieldOfView)
	{
		m_fieldOfView = fieldOfView;
	}

	float camera::getNearPlane() const
	{
		return m_nearPlane;
	}

	float camera::getFarPlane() const
	{
		return m_farPlane;
	}

	void camera::setNearAndFarPlanes(float nearPlane, float farPlane)
	{
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
	}

	m::mat4 camera::getOrientation() const
	{
		m::mat4 orientation;
		orientation = m::mat4::rotate(orientation, m::toRad(m_verticalAngle), m::vec3(1, 0, 0));
		orientation = m::mat4::rotate(orientation, m::toRad(m_horizontalAngle), m::vec3(0, 1, 0));
		return orientation;
	}

	void camera::setOffsetOrientation(float upAngle, float rightAngle)
	{
		m_horizontalAngle += rightAngle;
		m_verticalAngle += upAngle;
		normalizeAngles();
	}

	void camera::lookAt(const m::vec3& position)
	{
		m::vec3 direction = normalized(position - m_position);
		m_verticalAngle = m::toRad(asinf(-direction.y));
		m_horizontalAngle = -m::toRad(atan2f(-direction.x, -direction.z));
		normalizeAngles();
	}

	float camera::getViewportAspectRatio() const
	{
		return m_viewportAspectRatio;
	}

	void camera::setViewportAspectRatio(float viewportAspectRatio)
	{
		m_viewportAspectRatio = viewportAspectRatio;
	}

	m::vec3 camera::forward() const
	{
		m::vec4 forward = m::mat4::inverse(getOrientation()) * m::vec4(0, 0, -1, 1);
		return m::vec3(forward.x, forward.y, forward.z);
	}

	m::vec3 camera::right() const
	{
		m::vec4 right = m::mat4::inverse(getOrientation()) * m::vec4(1, 0, 0, 1);
		return m::vec3(right.x, right.y, right.z);
	}

	m::vec3 camera::up() const
	{
		m::vec4 up = m::mat4::inverse(getOrientation()) * m::vec4(0, 1, 0, 1);
		return m::vec3(up.x, up.y, up.z);
	}

	m::mat4 camera::matrix() const
	{
		return projection() * view();
	}

	m::mat4 camera::projection() const
	{
		return m::mat4::perspective(m::toRad(m_fieldOfView), m_viewportAspectRatio, m_nearPlane, m_farPlane);
	}

	m::mat4 camera::view() const
	{
		return getOrientation() * m::mat4::translate(m::mat4(), -m_position);
	}

	void camera::normalizeAngles()
	{
		m_horizontalAngle = fmodf(m_horizontalAngle, 360.0f);
		//fmodf can return negative values, but this will make them all positive
		if (m_horizontalAngle < 0.0f)
		{
			m_horizontalAngle += 360.0f;
		}

		if (m_verticalAngle > MaxVerticalAngle)
		{
			m_verticalAngle = MaxVerticalAngle;
		}
		else if (m_verticalAngle < -MaxVerticalAngle)
		{
			m_verticalAngle = -MaxVerticalAngle;
		}
	}
}