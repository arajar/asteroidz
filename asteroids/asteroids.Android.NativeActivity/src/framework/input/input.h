#pragma once

namespace input
{
	enum class Action
	{
		Down,
		Up,
		Move,
		Key,

		None,
	};

	struct TouchEvent
	{
		Action action = Action::None;
		size_t pointer = 0;
		float x = 0.f;
		float y = 0.f;
		float alpha = 0.f;
	};
}

#include "virtual_joystick.h"
