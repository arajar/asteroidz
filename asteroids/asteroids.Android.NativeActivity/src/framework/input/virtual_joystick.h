#pragma once

#include "../../game/entities/entity.h"
//////////////////////////////////////////////////////////////////////////

namespace input
{
	//////////////////////////////////////////////////////////////////////////

	struct virtualJoystick
	{
		math::vec2 m_position; // where the joystick is in the screen
		math::vec2 m_touchPosition; // where in the joystick are we touching
		math::vec2 m_thumbPosition;
		float m_angle;

		bool m_isTouching = false; // are we touching the joystick

		float m_radius;
		float m_thumbRadius = 25.f;
		float m_cuadrantSize = 20.f;
		float m_scale = 1.f;
		float m_acceleration = 0.f;

		math::vec2 m_velocity;

		math::mat4 m_projection;
		util::tweener<float> m_alpha;

		virtualJoystick() : m_background(nullptr), m_thumb(nullptr) {}
		~virtualJoystick();

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