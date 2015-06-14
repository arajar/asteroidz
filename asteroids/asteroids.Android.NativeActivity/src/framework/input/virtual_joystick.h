#pragma once

//////////////////////////////////////////////////////////////////////////

namespace input
{

	//	 Directions:
	//		-------------
	//		| / | 1 | \ |
	//		-------------
	//		| 8 | X | 2 |
	//		-------------
	//		| \ | 4 | / |
	//		-------------

	enum class Direction
	{
		NONE = -1,
		CENTER = NONE,

		TOP = 1,
		LEFT = 2,
		BOTTOM = 4,
		RIGHT = 8,

		TOP_LEFT = TOP | LEFT,
		TOP_RIGHT = TOP | RIGHT,
		BOTTOM_LEFT = BOTTOM | LEFT,
		BOTTOM_RIGHT = BOTTOM | RIGHT,
	};

	//////////////////////////////////////////////////////////////////////////

	struct virtualJoystick
	{
		math::vec2f m_position; // where the joystick is in the screen
		math::vec2f m_touchPosition; // where in the joystick are we touching
		math::vec2f m_oldPosition; // last touched position
		math::vec2f m_thumbPosition;
		math::vec2f m_delta;

		bool m_isTouching = false; // are we touching the joystick
		Direction m_currentDirection = Direction::CENTER;

		float m_radius = 60.f;
		float m_thumbRadius = 25.f;
		float m_cuadrantSize = 20.f;
		float m_scale = 1.f;

		math::vec2f m_velocity;

		void init();
		void handleInput(float x, float y);
		void render();
	};
}