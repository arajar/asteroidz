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
		math::vec2 m_position; // where the joystick is in the screen
		math::vec2 m_touchPosition; // where in the joystick are we touching
		math::vec2 m_oldPosition; // last touched position
		math::vec2 m_thumbPosition;
		math::vec2 m_delta;
		float m_angle;

		bool m_isTouching = false; // are we touching the joystick
		Direction m_currentDirection = Direction::CENTER;

		float m_radius;
		float m_thumbRadius = 25.f;
		float m_cuadrantSize = 20.f;
		float m_scale = 1.f;
		float m_acceleration = 0.f;

		math::vec2 m_velocity;

		math::mat4 m_projection;
		util::tweener<float> m_alpha;

		virtualJoystick() : m_background(nullptr), m_thumb(nullptr) {}

		void init(float radius = 160.f);
		void handleInput(const input::TouchEvent& ev);
		void render();
		void update(float deltaTime);

	private:
		void draw(const e::renderable& r, const math::vec2& pos);

	protected:
		e::renderable* m_background;
		e::renderable* m_thumb;
	};
}