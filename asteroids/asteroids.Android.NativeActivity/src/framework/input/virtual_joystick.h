#pragma once

#include "../../game/entities/entity.h"
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
		m::vec2 m_position; // where the joystick is in the screen
		m::vec2 m_touchPosition; // where in the joystick are we touching
		m::vec2 m_oldPosition; // last touched position
		m::vec2 m_thumbPosition;
		m::vec2 m_delta;

		bool m_isTouching = false; // are we touching the joystick
		Direction m_currentDirection = Direction::CENTER;

		float m_radius = 60.f;
		float m_thumbRadius = 25.f;
		float m_cuadrantSize = 20.f;
		float m_scale = 1.f;

		m::vec2 m_velocity;

		virtualJoystick() : m_background(nullptr), m_thumb(nullptr) {}

		void init();
		void handleInput(float x, float y);
		void render(const gfx::camera& cam);

	private:
		void draw(const gfx::camera& cam, const e::renderable& r, const m::vec2& pos, float radius);

	protected:
		e::renderable* m_background;
		e::renderable* m_thumb;
	};
}