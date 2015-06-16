#pragma once

namespace gfx
{
	class camera
	{
	public:
		camera();

	public:
		const m::vec3& getPosition() const;
		void setPosition(const m::vec3& position);
		void setOffsetPosition(const m::vec3& offset);

	public:
		float getFov() const;
		void setFov(float fov);

	public:
		float getNearPlane() const;
		float getFarPlane() const;

		void setNearAndFarPlanes(float nearPlane, float farPlane);

	public:
		m::mat4 getOrientation() const;

		void setOffsetOrientation(float upAngle, float rightAngle);
		void lookAt(const m::vec3& position);

	public:
		float getViewportAspectRatio() const;
		void setViewportAspectRatio(float viewportAspectRatio);

	public:
		m::vec3 forward() const;
		m::vec3 right() const;
		m::vec3 up() const;

		m::mat4 matrix() const;
		m::mat4 projection() const;
		m::mat4 view() const;

	private:
		void normalizeAngles();

	private:
		m::vec3 m_position;
		float m_horizontalAngle;
		float m_verticalAngle;
		float m_fieldOfView;
		float m_nearPlane;
		float m_farPlane;
		float m_viewportAspectRatio;
	};
}

